#pragma once

namespace FMS_5772 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MaintForm
	/// </summary>
	public ref class MaintForm : public System::Windows::Forms::Form
	{
	public:
		MaintForm(void)
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
		~MaintForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// MaintForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Name = L"MaintForm";
			this->Text = L"Maintaince";
			this->Load += gcnew System::EventHandler(this, &MaintForm::MaintForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MaintForm_Load(System::Object^  sender, System::EventArgs^  e) {
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