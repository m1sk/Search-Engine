#pragma once

#include "triesite.h"
#include <tuple>
#include <string>
#include <sstream>
#include <msclr\marshal.h>
using namespace std;
using namespace Library;

namespace FMS_5772 {
	

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for QueryForm
	/// </summary>
	public ref class QueryForm : public System::Windows::Forms::Form
	{
	public:
		QueryForm(triesite* _site,bool _admin, string* _sitepath)
		{
			site = _site;
			admin = _admin;
			sitepath = _sitepath;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	private: System::Windows::Forms::TextBox^  txtDownload;
	public: 

	public: 
	private: System::Windows::Forms::Button^  btnDownload;
	private: System::Windows::Forms::DataGridView^  dgvStatistics;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;

	protected:
		triesite* site;
		bool admin;
		string* sitepath;
	
		long count;
		long statCount;
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~QueryForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  query;
	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btnSearch;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::RadioButton^  rbQuery;
	private: System::Windows::Forms::RadioButton^  rbStats;
	private: System::Windows::Forms::Label^  txtResults;
	private: System::Windows::Forms::DataGridView^  dgvResults;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  docNameColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  searchColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  countColumn;
	private: System::Windows::Forms::Button^  btnDocSearch;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rBtnPercent;
	private: System::Windows::Forms::RadioButton^  rBtnCount;
	private: System::Windows::Forms::Button^  btnAllDocs;




	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->query = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->rbQuery = (gcnew System::Windows::Forms::RadioButton());
			this->rbStats = (gcnew System::Windows::Forms::RadioButton());
			this->txtResults = (gcnew System::Windows::Forms::Label());
			this->dgvResults = (gcnew System::Windows::Forms::DataGridView());
			this->docNameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->searchColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->countColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnDocSearch = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rBtnPercent = (gcnew System::Windows::Forms::RadioButton());
			this->rBtnCount = (gcnew System::Windows::Forms::RadioButton());
			this->btnAllDocs = (gcnew System::Windows::Forms::Button());
			this->txtDownload = (gcnew System::Windows::Forms::TextBox());
			this->btnDownload = (gcnew System::Windows::Forms::Button());
			this->dgvStatistics = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvResults))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvStatistics))->BeginInit();
			this->SuspendLayout();
			// 
			// query
			// 
			this->query->Location = System::Drawing::Point(56, 12);
			this->query->Name = L"query";
			this->query->Size = System::Drawing::Size(132, 20);
			this->query->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Search";
			// 
			// btnSearch
			// 
			this->btnSearch->Location = System::Drawing::Point(197, 12);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(75, 23);
			this->btnSearch->TabIndex = 2;
			this->btnSearch->Text = L"Search";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &QueryForm::btnSearch_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 58);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(37, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Result";
			// 
			// rbQuery
			// 
			this->rbQuery->AutoSize = true;
			this->rbQuery->Checked = true;
			this->rbQuery->Location = System::Drawing::Point(12, 38);
			this->rbQuery->Name = L"rbQuery";
			this->rbQuery->Size = System::Drawing::Size(61, 17);
			this->rbQuery->TabIndex = 4;
			this->rbQuery->TabStop = true;
			this->rbQuery->Text = L"Queries";
			this->rbQuery->UseVisualStyleBackColor = true;
			this->rbQuery->CheckedChanged += gcnew System::EventHandler(this, &QueryForm::rbQuery_CheckedChanged);
			// 
			// rbStats
			// 
			this->rbStats->AutoSize = true;
			this->rbStats->Location = System::Drawing::Point(70, 38);
			this->rbStats->Name = L"rbStats";
			this->rbStats->Size = System::Drawing::Size(67, 17);
			this->rbStats->TabIndex = 5;
			this->rbStats->Text = L"Statistics";
			this->rbStats->UseVisualStyleBackColor = true;
			// 
			// txtResults
			// 
			this->txtResults->AutoSize = true;
			this->txtResults->Location = System::Drawing::Point(67, 58);
			this->txtResults->Name = L"txtResults";
			this->txtResults->Size = System::Drawing::Size(0, 13);
			this->txtResults->TabIndex = 6;
			// 
			// dgvResults
			// 
			this->dgvResults->AllowUserToAddRows = false;
			this->dgvResults->AllowUserToDeleteRows = false;
			this->dgvResults->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvResults->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->docNameColumn, 
				this->searchColumn, this->countColumn});
			this->dgvResults->Location = System::Drawing::Point(15, 74);
			this->dgvResults->Name = L"dgvResults";
			this->dgvResults->ReadOnly = true;
			this->dgvResults->Size = System::Drawing::Size(240, 150);
			this->dgvResults->TabIndex = 7;
			// 
			// docNameColumn
			// 
			this->docNameColumn->HeaderText = L"Doc Name";
			this->docNameColumn->Name = L"docNameColumn";
			this->docNameColumn->ReadOnly = true;
			this->docNameColumn->Width = 50;
			// 
			// searchColumn
			// 
			this->searchColumn->HeaderText = L"Search";
			this->searchColumn->Name = L"searchColumn";
			this->searchColumn->ReadOnly = true;
			this->searchColumn->Width = 75;
			// 
			// countColumn
			// 
			this->countColumn->HeaderText = L"Count";
			this->countColumn->Name = L"countColumn";
			this->countColumn->ReadOnly = true;
			this->countColumn->Width = 75;
			// 
			// btnDocSearch
			// 
			this->btnDocSearch->Location = System::Drawing::Point(179, 230);
			this->btnDocSearch->Name = L"btnDocSearch";
			this->btnDocSearch->Size = System::Drawing::Size(76, 23);
			this->btnDocSearch->TabIndex = 8;
			this->btnDocSearch->Text = L"Search Doc";
			this->btnDocSearch->UseVisualStyleBackColor = true;
			this->btnDocSearch->Click += gcnew System::EventHandler(this, &QueryForm::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rBtnPercent);
			this->groupBox1->Controls->Add(this->rBtnCount);
			this->groupBox1->Location = System::Drawing::Point(143, 42);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(129, 29);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			// 
			// rBtnPercent
			// 
			this->rBtnPercent->AutoSize = true;
			this->rBtnPercent->Location = System::Drawing::Point(67, 9);
			this->rBtnPercent->Name = L"rBtnPercent";
			this->rBtnPercent->Size = System::Drawing::Size(62, 17);
			this->rBtnPercent->TabIndex = 1;
			this->rBtnPercent->Text = L"Percent";
			this->rBtnPercent->UseVisualStyleBackColor = true;
			// 
			// rBtnCount
			// 
			this->rBtnCount->AutoSize = true;
			this->rBtnCount->Checked = true;
			this->rBtnCount->Location = System::Drawing::Point(7, 9);
			this->rBtnCount->Name = L"rBtnCount";
			this->rBtnCount->Size = System::Drawing::Size(53, 17);
			this->rBtnCount->TabIndex = 0;
			this->rBtnCount->TabStop = true;
			this->rBtnCount->Text = L"Count";
			this->rBtnCount->UseVisualStyleBackColor = true;
			this->rBtnCount->CheckedChanged += gcnew System::EventHandler(this, &QueryForm::rBtnCount_CheckedChanged);
			// 
			// btnAllDocs
			// 
			this->btnAllDocs->Location = System::Drawing::Point(15, 231);
			this->btnAllDocs->Name = L"btnAllDocs";
			this->btnAllDocs->Size = System::Drawing::Size(102, 23);
			this->btnAllDocs->TabIndex = 10;
			this->btnAllDocs->Text = L"Show Searchable";
			this->btnAllDocs->UseVisualStyleBackColor = true;
			this->btnAllDocs->Click += gcnew System::EventHandler(this, &QueryForm::btnAllDocs_Click);
			// 
			// txtDownload
			// 
			this->txtDownload->Location = System::Drawing::Point(15, 269);
			this->txtDownload->Name = L"txtDownload";
			this->txtDownload->Size = System::Drawing::Size(148, 20);
			this->txtDownload->TabIndex = 11;
			// 
			// btnDownload
			// 
			this->btnDownload->Location = System::Drawing::Point(170, 265);
			this->btnDownload->Name = L"btnDownload";
			this->btnDownload->Size = System::Drawing::Size(75, 23);
			this->btnDownload->TabIndex = 12;
			this->btnDownload->Text = L"Download";
			this->btnDownload->UseVisualStyleBackColor = true;
			this->btnDownload->Click += gcnew System::EventHandler(this, &QueryForm::btnDownload_Click);
			// 
			// dgvStatistics
			// 
			this->dgvStatistics->AllowUserToAddRows = false;
			this->dgvStatistics->AllowUserToDeleteRows = false;
			this->dgvStatistics->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvStatistics->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->dataGridViewTextBoxColumn1, 
				this->dataGridViewTextBoxColumn3});
			this->dgvStatistics->Location = System::Drawing::Point(15, 74);
			this->dgvStatistics->Name = L"dgvStatistics";
			this->dgvStatistics->ReadOnly = true;
			this->dgvStatistics->Size = System::Drawing::Size(240, 150);
			this->dgvStatistics->TabIndex = 13;
			this->dgvStatistics->Visible = false;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"Doc Name";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"Count";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			// 
			// QueryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 297);
			this->Controls->Add(this->btnDownload);
			this->Controls->Add(this->txtDownload);
			this->Controls->Add(this->btnAllDocs);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnDocSearch);
			this->Controls->Add(this->dgvResults);
			this->Controls->Add(this->txtResults);
			this->Controls->Add(this->rbStats);
			this->Controls->Add(this->rbQuery);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->query);
			this->Controls->Add(this->dgvStatistics);
			this->Name = L"QueryForm";
			this->Text = L"QueryForm";
			this->Load += gcnew System::EventHandler(this, &QueryForm::QueryForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvResults))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvStatistics))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//download
		//statistics
		//
private: System::Void QueryForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 this->rbQuery->Visible = admin;
			 this->rbStats->Visible = admin;
		 }

private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e) {
			 try{
			 stringstream conv;
			 this->dgvResults->Visible = true;
			 if(this->rbQuery->Checked) {
				string query_exp((const char*)Marshal::StringToHGlobalAnsi(this->query->Text).ToPointer());
				list<string> matches = site->doclookup(query_exp);
				if(matches.size()==0)
				{
					 MessageBox::Show("No matches found");
					 return;
				}
				//list<std::tuple<string,string,long> > data;
				count = 0;
				this->rBtnCount->Checked = true;
				this->dgvResults->Rows->Clear();
				this->dgvResults->Rows->Add(matches.size());
				int i = 0;
				for(list<string>::const_iterator match
						= matches.begin(); match != matches.end(); ++match,++i)
				{
					int siteCount = site->expcount(*match,query_exp);
					 std::ostringstream oss;
					oss << siteCount;
    //return oss.str();
					this->dgvResults->Rows[i]->Cells[0]->Value = gcnew String((*match).c_str());
					this->dgvResults->Rows[i]->Cells[1]->Value = gcnew String(site->expsearch(*match,query_exp).c_str());
					this->dgvResults->Rows[i]->Cells[2]->Value = gcnew String(oss.str().c_str());
					//data.push_back(std::make_tuple(*match,
					//					site.expsearch(*match,query_exp),
					//					site.expcount(*match,query_exp)));
					if(siteCount > 0)
					{
						saveHitsForDoc((*match),loadHitsForDoc((*match))+1);
					}
					count += siteCount;
				}
				long total = site->listdoc(1).size();
				conv << count << " in " << total<<" documents";
				this->txtResults->Text = gcnew String(conv.str().c_str());
			//this->dgvResults->ItemsSource; //= List<Results> for query
			//Summary: docmatch_count " out of " doc_count " documents"
			//Fields: docname | line of first occurence | count/count%total_match
			}
				
			//this->txtResults->Text; //= result summary
			//this->dgvResults->ItemsSource; //= List<Results> for query
			//Summary: docmatched_count " out of " doc_count " documents"
			//Fields: docname | match_count/match_count%total_matches
			  }
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
			 }
		}
		 //search a selected doc
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			  if(this->dgvResults->SelectedRows->Count > 0)
			 {
				 string query_exp((const char*)Marshal::StringToHGlobalAnsi(this->query->Text).ToPointer());
				 string selectedDoc((const char*)Marshal::StringToHGlobalAnsi((String^)this->dgvResults->SelectedRows[0]->Cells[0]->Value).ToPointer());
				  if((selectedDoc.length()>2)&&(selectedDoc.at(selectedDoc.length()-1)=='*')==(selectedDoc.at(selectedDoc.length()-2)=='*'))
				 {
					 selectedDoc = selectedDoc.substr(0,selectedDoc.length()-2);
				 }
				  else
				  {
					  MessageBox::Show("You must select an indexed document!");
				  }
				 try{
					string search = site->expsearch(selectedDoc,query_exp);
					int expcount  = site->expcount(selectedDoc,query_exp);
					std::ostringstream oss;
					oss<<expcount;
					this->dgvResults->Rows->Clear();
					this->dgvResults->Rows->Add(1);
					this->dgvResults->Rows[0]->Cells[0]->Value = gcnew String(selectedDoc.c_str());
					this->dgvResults->Rows[0]->Cells[1]->Value = gcnew String(search.c_str());
					this->dgvResults->Rows[0]->Cells[2]->Value = gcnew String(oss.str().c_str());
					this->txtResults->Text = "";
					if(expcount > 0)
					{
						saveHitsForDoc(selectedDoc,loadHitsForDoc(selectedDoc)+1);
					}
				 }catch(exception e)
				 {
					MessageBox::Show(gcnew String(e.what()));
				 }
			 }
			 else
			 {
				  MessageBox::Show("Please Select A Document!");
			 }
		 }
private: System::Void rBtnCount_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 int c = (this->rbStats->Checked?1:2);
			 float div = (this->rbStats->Checked?statCount:count);
			 if(!this->rBtnCount->Checked)
			 {
				 
				for(int i=0;i<this->dgvResults->Rows->Count; i++)
				{
					std::ostringstream oss;
					oss << ((Int32::Parse((String^)this->dgvResults->Rows[i]->Cells[c]->Value))/div)*100.0;
					this->dgvResults->Rows[i]->Cells[c]->Value = gcnew String(oss.str().c_str());
			    }
			 }
			 else
			 {
				 for(int i=0;i<this->dgvResults->Rows->Count; i++)
				 {
					std::ostringstream oss;
					oss << ((Double::Parse((String^)this->dgvResults->Rows[i]->Cells[c]->Value))/100.0)*div;
					this->dgvResults->Rows[i]->Cells[c]->Value = gcnew String(oss.str().c_str());
				 }
			 }
		 }
private: System::Void btnAllDocs_Click(System::Object^  sender, System::EventArgs^  e) {
			list<string> docs;
			 try{
			 docs = site->listdoc(0);
			} 
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
				 return;
			 }
			if(docs.size() == 0)
			{
				 MessageBox::Show("No Docs in site");
				 return;
			}
			this->dgvResults->Rows->Clear();
			this->dgvResults->Rows->Add(docs.size());
			int i = 0;
			 for(list<string>::const_iterator doc
					= docs.begin(); doc != docs.end(); ++doc,++i)
			{
				 this->dgvResults->Rows[i]->Cells[0]->Value = gcnew String((*doc).c_str());
			}
		 }
private: System::Void rbQuery_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			bool q = this->rbQuery->Checked;
			this->btnAllDocs->Visible = q;
			this->btnDocSearch->Visible = q;
			this->dgvStatistics->Visible = !q;
			this->dgvResults->Visible = q;
			if(this->rbStats->Checked)
			{
				list<string> docs;
				 try{
				 docs = site->listdoc(0);
				 } 
				 catch(exception e)
				 {
					 MessageBox::Show(gcnew String(e.what()));
					 return;
				 }
				if(docs.size() == 0)
				{
					 MessageBox::Show("No Docs in site");
					 return;
				}
				this->dgvStatistics->Rows->Clear();
				this->dgvStatistics->Rows->Add(docs.size());
				int i = 0;
				statCount = 0;
				 for(list<string>::const_iterator doc
						= docs.begin(); doc != docs.end(); ++doc,++i)
				{
					string docChange = *doc;
					 if(((*doc).length()>2)&&((*doc).at((*doc).length()-1)=='*')==((*doc).at((*doc).length()-2)=='*'))
					 { 
						 docChange = doc->substr(0,(*doc).length()-2);
					 }
					 std::ostringstream oss;
					 int hitsForDoc=loadHitsForDoc(docChange); 
					 oss<<hitsForDoc;
					 this->dgvStatistics->Rows[i]->Cells[0]->Value = gcnew String(docChange.c_str());
					 this->dgvStatistics->Rows[i]->Cells[1]->Value = gcnew String(oss.str().c_str());
					 //add statistical intel
					 statCount+=hitsForDoc;
					 
				}
				 this->txtResults->Text = gcnew String("Total "+ statCount+" in " + i + "documents");
			}
		 }
private: System::Void btnDownload_Click(System::Object^  sender, System::EventArgs^  e) {
			  if(this->dgvResults->SelectedRows->Count > 0)
			 {
				 string downDest((const char*)Marshal::StringToHGlobalAnsi(this->txtDownload->Text).ToPointer());
				 string selectedDoc((const char*)Marshal::StringToHGlobalAnsi((String^)this->dgvResults->SelectedRows[0]->Cells[0]->Value).ToPointer());
				  if((selectedDoc.length()>2)&&(selectedDoc.at(selectedDoc.length()-1)=='*')==(selectedDoc.at(selectedDoc.length()-2)=='*'))
				 {
					 selectedDoc = selectedDoc.substr(0,selectedDoc.length()-2);
				 }
				 try{
					site->docdownload(selectedDoc,downDest);
				 }catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
			 }
			 }
			 else
			 {
				  MessageBox::Show("Please Select A Document!");
			 }
		 }
		 int loadHitsForDoc(string docname)
		 {
			 ifstream inf(*sitepath+'\\'+docname+"\\hits");
			 if(!inf)
			 {
				 //handle error
				 return 0;
			 }
			 int ret;
			 inf>>ret;
			 inf.close();
			 return ret;
		 }
		 void saveHitsForDoc(string docname,int hits)
		 {
			 ofstream of(*sitepath+'\\'+docname+"\\hits");
			 if(!of)
			 {
				 return;
			 }
			 of<<hits;
			 of.close();
		 }
		 
};
}