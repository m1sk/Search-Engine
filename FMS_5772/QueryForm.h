#pragma once

#include "triesite.h"
#include <tuple>
#include <string>
#include <sstream>
#include <msclr\marshal.h>
using namespace std;
using namespace Library;

namespace FMS_5772 {
	extern triesite site;
	extern bool admin;

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
		QueryForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvResults))->BeginInit();
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
			this->label2->TabIndex = 3;
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
			// 
			// rbStats
			// 
			this->rbStats->AutoSize = true;
			this->rbStats->Location = System::Drawing::Point(103, 38);
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
			this->dgvResults->Location = System::Drawing::Point(15, 75);
			this->dgvResults->Name = L"dgvResults";
			this->dgvResults->ReadOnly = true;
			this->dgvResults->Size = System::Drawing::Size(240, 150);
			this->dgvResults->TabIndex = 7;
			this->dgvResults->Visible = false;
			// 
			// QueryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->dgvResults);
			this->Controls->Add(this->txtResults);
			this->Controls->Add(this->rbStats);
			this->Controls->Add(this->rbQuery);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->query);
			this->Name = L"QueryForm";
			this->Text = L"QueryForm";
			this->Load += gcnew System::EventHandler(this, &QueryForm::QueryForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dgvResults))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
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
				list<string> matches = site.doclookup(query_exp);
				list<std::tuple<string,string,long> > data;
				long count = 0;
				for(list<string>::const_iterator match
						= matches.begin(); match != matches.end(); ++match)
				{
					data.push_back(std::make_tuple(*match,
										site.expsearch(*match,query_exp),
										site.expcount(*match,query_exp)));
					count += site.expcount(*match, query_exp);
				}
				long total = site.listdoc(1).size();
				conv << count << " out of " << total;
				this->txtResults->Text = gcnew String(conv.str().c_str());
			//this->dgvResults->ItemsSource; //= List<Results> for query
			//Summary: docmatch_count " out of " doc_count " documents"
			//Fields: docname | line of first occurence | count/count%total_match
			}
			else if(this->rbStats) {
			//this->txtResults->Text; //= result summary
			//this->dgvResults->ItemsSource; //= List<Results> for query
			//Summary: docmatched_count " out of " doc_count " documents"
			//Fields: docname | match_count/match_count%total_matches
			}
			  }
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
			 }
		}
};
}