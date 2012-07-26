#pragma once
#include "triesite.h"
#include <string>
#include "QueryForm.h"
#include "MaintForm.h"

using namespace std;
using namespace Library;

namespace FMS_5772 {
	triesite site;
	bool admin;
	string sitepath;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  maintain;
	private: System::Windows::Forms::TextBox^  txtUser;
	private: System::Windows::Forms::TextBox^  txtPass;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  btnLogin;
	private: System::Windows::Forms::Button^  query;
	private: System::Windows::Forms::TextBox^  txtPath;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	protected: 


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->maintain = (gcnew System::Windows::Forms::Button());
			this->txtUser = (gcnew System::Windows::Forms::TextBox());
			this->txtPass = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->query = (gcnew System::Windows::Forms::Button());
			this->txtPath = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 209);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 2;
			// 
			// maintain
			// 
			this->maintain->Location = System::Drawing::Point(121, 106);
			this->maintain->Name = L"maintain";
			this->maintain->Size = System::Drawing::Size(151, 36);
			this->maintain->TabIndex = 3;
			this->maintain->Text = L"Maintenance";
			this->maintain->UseVisualStyleBackColor = true;
			this->maintain->Visible = false;
			this->maintain->Click += gcnew System::EventHandler(this, &MainForm::maintain_Click);
			// 
			// txtUser
			// 
			this->txtUser->Location = System::Drawing::Point(15, 83);
			this->txtUser->Name = L"txtUser";
			this->txtUser->Size = System::Drawing::Size(100, 20);
			this->txtUser->TabIndex = 4;
			// 
			// txtPass
			// 
			this->txtPass->Location = System::Drawing::Point(15, 122);
			this->txtPass->Name = L"txtPass";
			this->txtPass->Size = System::Drawing::Size(100, 20);
			this->txtPass->TabIndex = 5;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 67);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Username";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(15, 106);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Password";
			// 
			// btnLogin
			// 
			this->btnLogin->Location = System::Drawing::Point(15, 148);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(75, 23);
			this->btnLogin->TabIndex = 8;
			this->btnLogin->Text = L"Allow Main.";
			this->btnLogin->UseVisualStyleBackColor = true;
			this->btnLogin->Click += gcnew System::EventHandler(this, &MainForm::btnLogin_Click);
			// 
			// query
			// 
			this->query->Location = System::Drawing::Point(121, 67);
			this->query->Name = L"query";
			this->query->Size = System::Drawing::Size(151, 36);
			this->query->TabIndex = 9;
			this->query->Text = L"Query";
			this->query->UseVisualStyleBackColor = true;
			this->query->Click += gcnew System::EventHandler(this, &MainForm::query_Click);
			// 
			// txtPath
			// 
			this->txtPath->Location = System::Drawing::Point(12, 12);
			this->txtPath->Name = L"txtPath";
			this->txtPath->Size = System::Drawing::Size(260, 20);
			this->txtPath->TabIndex = 10;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(15, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(125, 23);
			this->button1->TabIndex = 11;
			this->button1->Text = L"Mount";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(144, 38);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(128, 23);
			this->button2->TabIndex = 12;
			this->button2->Text = L"Unmount";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 177);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->txtPath);
			this->Controls->Add(this->query);
			this->Controls->Add(this->btnLogin);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txtPass);
			this->Controls->Add(this->txtUser);
			this->Controls->Add(this->maintain);
			this->Controls->Add(this->label1);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Name = L"MainForm";
			this->Text = L"Main Menu";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 this->query->Visible = false;
			 this->button2->Visible = false;
		 }
private: System::Void btnLogin_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->maintain->Visible = admin = 
				 ((this->txtUser->Text == "admin") && (this->txtPass->Text == "system"));
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 try{
				 sitepath = (const char*)Marshal::StringToHGlobalAnsi(this->txtPath->Text).ToPointer();
			site.mount((const char*)Marshal::StringToHGlobalAnsi(this->txtPath->Text).ToPointer());
			 }
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
			 }
			list<string> docs = site.listdoc(0);
			 this->query->Visible = true;
			 this->button1->Visible = false;
			 this->button2->Visible = true;
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 try{
			 site.unmount();
			  }
			 catch(exception e)
			 {
				 MessageBox::Show(gcnew String(e.what()));
			 }
			 this->query->Visible = false;
			 this->button1->Visible = true;
			 this->button2->Visible = false;
		 }
private: System::Void query_Click(System::Object^  sender, System::EventArgs^  e) {
			 (gcnew QueryForm())->Show();
		 }
private: System::Void maintain_Click(System::Object^  sender, System::EventArgs^  e) {
			 (gcnew MaintForm())->Show();
		 }
};
}

