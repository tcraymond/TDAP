#pragma once

#include <sstream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;


namespace TDAP {

	/// <summary>
	/// Summary for frmConsole
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmConsole : public System::Windows::Forms::Form
	{
	public:
		frmConsole(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	//	ostringstream* consoleStream;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmConsole()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(0, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(463, 278);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// frmConsole
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(463, 278);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"frmConsole";
			this->Text = L"frmConsole";
			this->Load += gcnew System::EventHandler(this, &frmConsole::frmConsole_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void frmConsole_Load(System::Object^  sender, System::EventArgs^  e) {
				 
				 //richTextBox1->LoadFile((*consoleStream).str(), RichTextBoxStreamType::PlainText);
			 }
			 public: 
	//		 System::Void setText(string* newText){
	//			richTextBox1->Text = gcnew String(newText->c_str());
	//		 }
	};

}
