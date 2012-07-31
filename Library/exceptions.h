#pragma once
#include <stdexcept>
#include <string>
using namespace std;

namespace Library {

	/*
	* This library includes common functions involving exceptions
	* 
	*/

	struct DocException: runtime_error
	{
		DocException(string s)
			: runtime_error(s.c_str()) {}
	};

	struct SiteException: runtime_error
	{
		SiteException(string s, bool exists = false)
			: runtime_error("Couldn't " + s + " because" +
			(exists? " it exists" : " there is no doc by that name")) {}
	};

	struct FileException : runtime_error
	{
		FileException(string s)
			: runtime_error(s + "\nCause: " + strerror(errno)) {}
	};

	struct SystemException: runtime_error
	{
		SystemException(string s)
			: runtime_error(s) {}
	};

	struct ParseException: runtime_error
	{
		ParseException(string s)
			: runtime_error("Malformed search query\n" + s) {}
	};
}
