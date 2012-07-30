#pragma once
#include <list>
#include <string>
#include <regex>
#include <sstream>
#include <limits>
#include "trienode.h"
using namespace std;

namespace Library {

	/*
	* This library includes common functions involving parsing complex search expressions
	* 
	*/

	template<class T>
	class WordSearcher
	{
		static const bool IS_VALID = T::IS_A_FIELD;
		// dynamic array used when creating and searching trietree
		triebuffer buf;
		WordSearcher();
	public:
		WordSearcher(triebuffer _buf) : buf(_buf)	{}
		long operator()(string word) { return letters(word, 0);}
		T letters(string word, long node);
		T wildcard(string word, long node);
	};

	template<class T>
	T WordSearcher<T>::letters(string word, long node)
	{
		buf[node].print_node();
		cerr << "Expression: " << word << "\n";

		T ret;
		long nextNode = -1;
		if(word.length() == 0)
			return T::MIN();
		for(unsigned long w = 0;w < word.length();w++)
		{
			if(word[w] == '*')
			{
				ret = wildcard(word.substr(w+1,word.length()-1), node);
				if(ret != T::MIN())
					return ret;
			}
			node = buf[node].links[word[w]];
			if(node == trienode::INVALID_NODE)
				return T::MIN();
		}
		// Debugging
		 cerr << word <<" Last char:" << word[word.length()-1] << endl;
		
		if((word[word.length()-1] == '*') && ((ret = wildcard(word, nextNode))!= -1))
			return ret;
		else
			nextNode = buf[nextNode].links[word[word.length()-1]];
		
		if(buf[node].wordend)
			return (T) buf[node];
		return T::MIN();
	}

	template<class T>
	T WordSearcher<T>::wildcard(string word, long node)
	{
		buf[node].print_node();
		cerr << "Expression: " << word << "\n";

		long link = trienode::INVALID_NODE;
		T comp;
		if(word != "")
			comp = this->letters(word, node);
		for(long i = 0; i <trienode::LINKS_LENGTH;i++  )
		{
			link = buf[node].links[i]; 
			if(link != trienode::INVALID_NODE)
			{
				if(buf[link].wordend && (word==""))
					comp = comp + T(buf[link]);
				comp = comp + wildcard(word, link);

			}
		}
		if(comp == T::MAX()) 
			return T::MIN();
		return comp;
	}

	template<class T>
	class AtomSearcher
	{
		static const bool IS_VALID = T::IS_A_FIELD;
		// dynamic array used when creating and searching trietree
		triebuffer buf;
		AtomSearcher();
	public:
		AtomSearcher(triebuffer _buf) : buf(_buf) {}
		long operator()(vector<string> expr);
	};

	template<class T>
	long AtomSearcher<T>::operator()(vector<string> expr)
	{
		vector<T> values;
		values.resize(expr.size());
		transform(expr.begin(), expr.end(), values.begin(), WordSearcher<T>(buf));
		T comp;
		for(vector<T>::iterator i = values.begin(); i != values.end(); ++i)
			comp = comp + *i;
		if(comp == T::MAX())
			return T::MIN();
		return comp;
	}
	
	struct Field
	{
		static const bool IS_A_FIELD = true;
		long value;
		virtual long operator&(long rhs) = 0;
		virtual long operator|(long rhs) = 0;
		virtual long operator+(long rhs) = 0;
		bool operator<(Field& rhs) {return value < rhs.value;}
		bool operator==(Field& rhs) {return value == rhs.value;}
		operator long() { return value;}
	};

	struct Occurence : Field
	{
		Occurence() { value = Occurence::MAX();}
		Occurence(long _v) { value = _v;}
		Occurence(trienode n) { value = n.firstoffset;}
		long operator&(long rhs) { return min(value, rhs);}
		long operator|(long rhs) { long x=value, y=rhs; if(x==-1) return y; if(y==-1) return x; return min(x,y);}
		long operator+(long rhs) { return *this | rhs;}
		static long MIN() { return -1;}
		static long MAX() { return LONG_MAX;}
	};

	struct Count : Field
	{
		Count() { value = Count::MAX();}
		Count(long _v) { value = _v;}
		Count(trienode n) { value = n.nrofoccurences;}
		long operator&(long rhs) { return value * rhs;}
		long operator|(long rhs) { return value + rhs;}
		long operator+(long rhs) { return *this | rhs;}
		static long MIN() { return 0;}
		static long MAX() { return 0;}
	};

	static vector<vector<string> > get_atoms(const string input) {
		vector<vector<string> > ret;
		vector<string> atom;
		regex rgx("\\([^()]*\\)");
		string tmp;
		for(sregex_iterator it(input.begin(), input.end(), rgx), it_end; it != it_end; ++it) {
			if((*it)[0].matched)
			{
				tmp = (*it)[0].str().substr(1, (*it)[0].str().length() - 2);
				stringstream splitter(tmp);
				do {
					string sub;
					splitter >> sub;
					atom.push_back(sub);
				} while(splitter && splitter.rdbuf()->in_avail());
				ret.push_back(atom);
				atom.clear();
			}
		}
		return ret;
	}

	static string replace_atoms(string input) {
		regex rgx("\\([^()]*\\)");
		long loc = 0, i = 0;
		stringstream out;
		for(sregex_iterator it(input.begin(), input.end(), rgx), it_end; it != it_end; ++it) {
			out << input.substr(i, it->position() - i);
			i = it->position() + it->length();
			out << '#' << loc++;
		}
		out << input.substr(i, input.length() - i);
		return out.str();
	}

	bool is_operator(const char c) { return (c == '|' || c == '&'); }
	bool is_ident(const char c)    { return (c == '#'); }
	bool is_digit(const char c)    { return (c >= '0') && (c <= '9'); }

	template<class T>
	static void eval(char sc, vector<T>& var_stack, vector<char>& op_stack)
	{
		bool IS_VALID = T::IS_A_FIELD;
		T x = var_stack.back(); var_stack.pop_back();
		T y = var_stack.back(); var_stack.pop_back();
		if(sc == '&')
			var_stack.push_back(x & y);
		else
			var_stack.push_back(x | y);
	}

	template<class T>
	static long shunting_yard(const string input, const vector<T> vars)
	{
		bool IS_VALID = T::IS_A_FIELD;
		vector<T>    var_stack;
		vector<char> op_stack;
		char c;
		char sc;          // used for record stack element
 
		for(string::const_iterator i = input.begin(); i != input.end(); ++i) {
			// read one token from the input stream
			c = *i;
			if(c != ' ')    {
				// If the token is a number (identifier), then add it to the output queue.
				if(is_ident(c))  {
					++i;
					string::const_iterator j = i;
					for(; j != input.end() && is_digit(*j); ++j);
					var_stack.push_back(vars.at(atoi(string(i,j).c_str())));
					i = j - 1;
				}
				// If the token is an operator, op1, then:
				else if(is_operator(c))  {
					while(!op_stack.empty()) {
						sc = op_stack.back();
						// While there is an operator token, o2, at the top of the stack
						// op1 is left-associative and its precedence is less than or equal to that of op2,
						// or op1 is right-associative and its precedence is less than that of op2,
						if(is_operator(sc))
							eval(sc, var_stack, op_stack);
						else
							break;
					}
					// push op1 onto the stack.
					op_stack.push_back(c);
				}
				// If the token is an open-paren, then push it onto the stack.
				else if(c == '(')
					op_stack.push_back(c);
				// If the token is a close-paren:
				else if(c == ')')
				{
					bool pe = false;
					// Until the token at the top of the stack is an open-paren,
					// pop operators off the stack onto the output queue
					while(!op_stack.empty())
					{
						sc = op_stack.back();
						if(sc == '(')
						{
							pe = true;
							break;
						}
						else
						{
							eval(sc, var_stack, op_stack);
							op_stack.pop_back();
						}
					}
					// If the stack runs out without finding an open-paren, then there are mismatched parentheses.
					if(!pe)
						throw exception("Error: mismatched parentheses");
					// Pop the open parenthesis from the stack, but not onto the output queue.
					op_stack.pop_back();
				}
				else // Unknown token
					throw exception(string("Unknown token ").append(1, c).c_str());
			}
		}
		// When there are no more tokens to read:
		// While there are still operator tokens in the stack:
		while(!op_stack.empty())
		{
			sc = op_stack.back();
			if(sc == '(' || sc == ')')
				throw exception("Error: mismatched parentheses");
			eval(sc, var_stack, op_stack);
			op_stack.pop_back();
		}
		if(var_stack.size() != 1)
			throw exception("Error: more operands than operators");
		return var_stack.back();
	}
}

