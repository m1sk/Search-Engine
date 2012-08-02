#pragma once
#include "triesite.h"
#include <string>
#include <sstream>
#include <msclr\marshal.h>
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
	/// Summary for MaintForm
	/// </summary>
	public ref class MaintForm : public System::Windows::Forms::Form
	{
	public:
		MaintForm(triesite* _site,bool _admin,string* _sitepath)
		{
			site = _site;
			admin = _admin;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		triesite* site;
	bool admin;
	string* sitepath;
	
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MaintForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  btnCreate;
	private: System::Windows::Forms::Button^  btnUpload;
	protected: 


	private: System::Windows::Forms::DataGridView^  docListView;
	private: System::Windows::Forms::Button^  btnIndex;

	private: System::Windows::Forms::Button^  btnDelete;
	private: System::Windows::Forms::RadioButton^  rBtnCopy;
	private: System::Windows::Forms::RadioButton^  rBtnMove;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  rBtnPhysic;
	private: System::Windows::Forms::RadioButton^  rBtnLogic;




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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnCreate = (gcnew System::Windows::Forms::Button());
			this->btnUpload = (gcnew System::Windows::Forms::Button());
			this->docListView = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnIndex = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->rBtnCopy = (gcnew System::Windows::Forms::RadioButton());
			this->rBtnMove = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rBtnPhysic = (gcnew System::Windows::Forms::RadioButton());
			this->rBtnLogic = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->docListView))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(13, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(243, 20);
			this->textBox1->TabIndex = 0;
			// 
			// btnCreate
			// 
			this->btnCreate->Location = System::Drawing::Point(262, 13);
			this->btnCreate->Name = L"btnCreate";
			this->btnCreate->Size = System::Drawing::Size(75, 23);
			this->btnCreate->TabIndex = 1;
			this->btnCreate->Text = L"Create Site";
			this->btnCreate->UseVisualStyleBackColor = true;
			this->btnCreate->Click += gcnew System::EventHandler(this, &MaintForm::button1_Click);
			// 
			// btnUpload
			// 
			this->btnUpload->Location = System::Drawing::Point(12, 39);
			this->btnUpload->Name = L"btnUpload";
			this->btnUpload->Size = System::Drawing::Size(111, 23);
			this->btnUpload->TabIndex = 2;
			this->btnUpload->Text = L"Upload Document";
			this->btnUpload->UseVisualStyleBackColor = true;
			this->btnUpload->Click += gcnew System::EventHandler(this, &MaintForm::btnUpload_Click);
			// 
			// docListView
			// 
			this->docListView->AllowUserToAddRows = false;
			this->docListView->AllowUserToDeleteRows = false;
			this->docListView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->docListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1) {this->dataGridViewTextBoxColumn1});
			this->docListView->Location = System::Drawing::Point(13, 69);
			this->docListView->Name = L"docListView";
			this->docListView->ReadOnly = true;
			this->docListView->Size = System::Drawing::Size(240, 117);
			this->docListView->TabIndex = 3;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"Doc Name";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			// 
			// btnIndex
			// 
			this->btnIndex->Location = System::Drawing::Point(13, 193);
			this->btnIndex->Name = L"btnIndex";
			this->btnIndex->Size = System::Drawing::Size(75, 23);
			this->btnIndex->TabIndex = 4;
			this->btnIndex->Text = L"Index";
			this->btnIndex->UseVisualStyleBackColor = true;
			this->btnIndex->Click += gcnew System::EventHandler(this, &MaintForm::btnIndex_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Location = System::Drawing::Point(104, 193);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(75, 23);
			this->btnDelete->TabIndex = 5;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &MaintForm::btnDelete_Click);
			// 
			// rBtnCopy
			// 
			this->rBtnCopy->AutoSize = true;
			this->rBtnCopy->Checked = true;
			this->rBtnCopy->Location = System::Drawing::Point(130, 44);
			this->rBtnCopy->Name = L"rBtnCopy";
			this->rBtnCopy->Size = System::Drawing::Size(49, 17);
			this->rBtnCopy->TabIndex = 6;
			this->rBtnCopy->TabStop = true;
			this->rBtnCopy->Text = L"Copy";
			this->rBtnCopy->UseVisualStyleBackColor = true;
			// 
			// rBtnMove
			// 
			this->rBtnMove->AutoSize = true;
			this->rBtnMove->Location = System::Drawing::Point(177, 45);
			this->rBtnMove->Name = L"rBtnMove";
			this->rBtnMove->Size = System::Drawing::Size(52, 17);
			this->rBtnMove->TabIndex = 7;
			this->rBtnMove->Text = L"Move";
			this->rBtnMove->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rBtnPhysic);
			this->groupBox1->Controls->Add(this->rBtnLogic);
			this->groupBox1->Location = System::Drawing::Point(185, 192);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(130, 36);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Delete Type";
			// 
			// rBtnPhysic
			// 
			this->rBtnPhysic->AutoSize = true;
			this->rBtnPhysic->Checked = true;
			this->rBtnPhysic->Location = System::Drawing::Point(72, 13);
			this->rBtnPhysic->Name = L"rBtnPhysic";
			this->rBtnPhysic->Size = System::Drawing::Size(64, 17);
			this->rBtnPhysic->TabIndex = 1;
			this->rBtnPhysic->TabStop = true;
			this->rBtnPhysic->Text = L"Physical";
			this->rBtnPhysic->UseVisualStyleBackColor = true;
			// 
			// rBtnLogic
			// 
			this->rBtnLogic->AutoSize = true;
			this->rBtnLogic->Location = System::Drawing::Point(6, 13);
			this->rBtnLogic->Name = L"rBtnLogic";
			this->rBtnLogic->Size = System::Drawing::Size(59, 17);
			this->rBtnLogic->TabIndex = 0;
			this->rBtnLogic->Text = L"Logical";
			this->rBtnLogic->UseVisualStyleBackColor = true;
			// 
			// MaintForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(349, 262);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->rBtnMove);
			this->Controls->Add(this->rBtnCopy);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnIndex);
			this->Controls->Add(this->docListView);
			this->Controls->Add(this->btnUpload);
			this->Controls->Add(this->btnCreate);
			this->Controls->Add(this->textBox1);
			this->Name = L"MaintForm";
			this->Text = L"Maintaince";
			this->Load += gcnew System::EventHandler(this, &MaintForm::MaintForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->docListView))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MaintForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 list<string> docList;
				 try{
				 docList = site->listdoc(0); 
				 }
				 catch(exception e)
				 {
					 MessageBox::Show(gcnew String(e.what()));
					 this->Close();
				 } 
				 list<string>::iterator it = docList.begin();
				 this->docListView->Rows->Add(docList.size());
				 for(unsigned int i = 0; i <  docList.size();i++,it++)
				 {
					this->docListView->Rows[i]->Cells[0]->Value = gcnew String((*it).c_str());
				 }
				 
			 }
	private: System::Void btnUpload_Click(System::Object^  sender, System::EventArgs^  e) {
				 try{
				 site->docupload((const char*)Marshal::StringToHGlobalAnsi(this->textBox1->Text).ToPointer(),(this->rBtnCopy->Checked?'C':'M'));
				  }
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
				 return;
			 }
		 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 try{
				 //set sitepath
				 *sitepath = getCurrentPath()+"\\"+(const char*)Marshal::StringToHGlobalAnsi(this->textBox1->Text).ToPointer();
				 site->create((const char*)Marshal::StringToHGlobalAnsi(this->textBox1->Text).ToPointer());
			  }
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
			 }
		 }
private: System::Void btnIndex_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(this->docListView->SelectedRows->Count > 0)
			 {
				 string selectedDoc((const char*)Marshal::StringToHGlobalAnsi((String^)this->docListView->SelectedRows[0]->Cells[0]->Value).ToPointer());
				 if((selectedDoc.length()>2)&&(selectedDoc.at(selectedDoc.length()-1)=='*')==(selectedDoc.at(selectedDoc.length()-2)=='*'))
				 {
					 selectedDoc = selectedDoc.substr(0,selectedDoc.length()-2);
				 }
				 try{
				 site->docidx(selectedDoc);
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
private: System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e) {
			  if(this->docListView->SelectedRows->Count > 0)
			 {
				 string selectedDoc((const char*)Marshal::StringToHGlobalAnsi((String^)this->docListView->SelectedRows[0]->Cells[0]->Value).ToPointer());
				 if((selectedDoc.length()>2)&&(selectedDoc.at(selectedDoc.length()-1)=='*')==(selectedDoc.at(selectedDoc.length()-2)=='*'))
				 {
					 selectedDoc = selectedDoc.substr(0,selectedDoc.length()-2);
				 }
				 try{
					 MessageBox::Show(this->rBtnLogic->Checked?"L":"P");
				 site->docdel(selectedDoc,(this->rBtnLogic->Checked?'L':'P'));
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
};
}
/* Supports:
 * create - path
 * del    - void
 *
 * docupload   - path + copy/move
 * docdownload - path + dest
 *
 * docidx - name
 * docdel - name + log/phy
 */