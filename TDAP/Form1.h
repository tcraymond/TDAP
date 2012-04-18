#pragma once

#include "Transformer.h"
#include "frmConsole.h"
#include <sstream>

namespace TDAP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	using namespace System::Xml::Serialization;
	using namespace System::IO;
	using namespace System::Threading;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			transformer = gcnew Transformer();
			treeTfmr->Nodes->Add("Transformer", "Transformer");
			tdapFileName = "";
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TreeView^  treeTfmr;
	protected: 





	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Panel^  pnlWinding;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  pnlTransformer;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;


	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  txtWdgMVA;

	private: System::Windows::Forms::ComboBox^  cmbWdgConn;

	private: System::Windows::Forms::TextBox^  txtWdgVoltage;

	private: System::Windows::Forms::TextBox^  txtWdgName;

	private: System::Windows::Forms::Panel^  pnlSection;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  txtHeight;
	private: System::Windows::Forms::TextBox^  txtOuterRad;
	private: System::Windows::Forms::TextBox^  txtInnerRad;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  txtStdsPerTrn;
	private: System::Windows::Forms::TextBox^  txtTurnsAxi;
	private: System::Windows::Forms::TextBox^  txtTurnsRad;
	private: System::Windows::Forms::TextBox^  txtHtAbvYoke;
	private: System::Windows::Forms::TextBox^  txtSecName;

	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::RadioButton^  opt3Ph;


	private: System::Windows::Forms::RadioButton^  opt1Ph;

	private: System::Windows::Forms::TextBox^  txtXfmrName;

	private: System::Windows::Forms::TextBox^  txtMVA;


	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  txtDistWdgTnk;

	private: System::Windows::Forms::TextBox^  txtCoreWinHt;

	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Button^  btnDeleteWinding;

	private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::Button^  btnAddWinding;


	private: System::Windows::Forms::TextBox^  txtLegRad;

private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  contentsToolStripMenuItem;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::RadioButton^  optCurrentNeg;

private: System::Windows::Forms::RadioButton^  optCurrentPos;





			 Transformer^ transformer;
private: System::Windows::Forms::ToolStripMenuItem^  runToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  writeGMSHFileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  showPlotToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  showConsoleToolStripMenuItem;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::RadioButton^  radioButton3;
private: System::Windows::Forms::RadioButton^  radioButton2;
private: System::Windows::Forms::RadioButton^  radioButton1;
private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::RadioButton^  radioButton5;
private: System::Windows::Forms::RadioButton^  radioButton4;



		 String^ tdapFileName;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->treeTfmr = (gcnew System::Windows::Forms::TreeView());
			this->pnlWinding = (gcnew System::Windows::Forms::Panel());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->optCurrentNeg = (gcnew System::Windows::Forms::RadioButton());
			this->optCurrentPos = (gcnew System::Windows::Forms::RadioButton());
			this->btnDeleteWinding = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->txtWdgMVA = (gcnew System::Windows::Forms::TextBox());
			this->cmbWdgConn = (gcnew System::Windows::Forms::ComboBox());
			this->txtWdgVoltage = (gcnew System::Windows::Forms::TextBox());
			this->txtWdgName = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pnlTransformer = (gcnew System::Windows::Forms::Panel());
			this->btnAddWinding = (gcnew System::Windows::Forms::Button());
			this->txtLegRad = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->txtMVA = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->txtDistWdgTnk = (gcnew System::Windows::Forms::TextBox());
			this->txtCoreWinHt = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->opt3Ph = (gcnew System::Windows::Forms::RadioButton());
			this->opt1Ph = (gcnew System::Windows::Forms::RadioButton());
			this->txtXfmrName = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->writeGMSHFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showPlotToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->showConsoleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contentsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pnlSection = (gcnew System::Windows::Forms::Panel());
			this->txtSecName = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->txtStdsPerTrn = (gcnew System::Windows::Forms::TextBox());
			this->txtTurnsAxi = (gcnew System::Windows::Forms::TextBox());
			this->txtTurnsRad = (gcnew System::Windows::Forms::TextBox());
			this->txtHtAbvYoke = (gcnew System::Windows::Forms::TextBox());
			this->txtHeight = (gcnew System::Windows::Forms::TextBox());
			this->txtOuterRad = (gcnew System::Windows::Forms::TextBox());
			this->txtInnerRad = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->pnlWinding->SuspendLayout();
			this->pnlTransformer->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->pnlSection->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// treeTfmr
			// 
			this->treeTfmr->Location = System::Drawing::Point(12, 38);
			this->treeTfmr->Name = L"treeTfmr";
			this->treeTfmr->Size = System::Drawing::Size(187, 319);
			this->treeTfmr->TabIndex = 0;
			this->treeTfmr->BeforeSelect += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &Form1::treeTfmr_BeforeSelect);
			this->treeTfmr->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Form1::treeTfmr_AfterSelect);
			// 
			// pnlWinding
			// 
			this->pnlWinding->Controls->Add(this->label19);
			this->pnlWinding->Controls->Add(this->optCurrentNeg);
			this->pnlWinding->Controls->Add(this->optCurrentPos);
			this->pnlWinding->Controls->Add(this->btnDeleteWinding);
			this->pnlWinding->Controls->Add(this->button4);
			this->pnlWinding->Controls->Add(this->txtWdgMVA);
			this->pnlWinding->Controls->Add(this->cmbWdgConn);
			this->pnlWinding->Controls->Add(this->txtWdgVoltage);
			this->pnlWinding->Controls->Add(this->txtWdgName);
			this->pnlWinding->Controls->Add(this->label6);
			this->pnlWinding->Controls->Add(this->label5);
			this->pnlWinding->Controls->Add(this->label4);
			this->pnlWinding->Controls->Add(this->label3);
			this->pnlWinding->Location = System::Drawing::Point(205, 39);
			this->pnlWinding->Name = L"pnlWinding";
			this->pnlWinding->Size = System::Drawing::Size(400, 315);
			this->pnlWinding->TabIndex = 5;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(152, 137);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(89, 13);
			this->label19->TabIndex = 12;
			this->label19->Text = L"Current Direction:";
			// 
			// optCurrentNeg
			// 
			this->optCurrentNeg->AutoSize = true;
			this->optCurrentNeg->Location = System::Drawing::Point(287, 135);
			this->optCurrentNeg->Name = L"optCurrentNeg";
			this->optCurrentNeg->Size = System::Drawing::Size(28, 17);
			this->optCurrentNeg->TabIndex = 11;
			this->optCurrentNeg->TabStop = true;
			this->optCurrentNeg->Text = L"-";
			this->optCurrentNeg->UseVisualStyleBackColor = true;
			// 
			// optCurrentPos
			// 
			this->optCurrentPos->AutoSize = true;
			this->optCurrentPos->Location = System::Drawing::Point(253, 135);
			this->optCurrentPos->Name = L"optCurrentPos";
			this->optCurrentPos->Size = System::Drawing::Size(31, 17);
			this->optCurrentPos->TabIndex = 10;
			this->optCurrentPos->TabStop = true;
			this->optCurrentPos->Text = L"+";
			this->optCurrentPos->UseVisualStyleBackColor = true;
			// 
			// btnDeleteWinding
			// 
			this->btnDeleteWinding->Location = System::Drawing::Point(148, 230);
			this->btnDeleteWinding->Name = L"btnDeleteWinding";
			this->btnDeleteWinding->Size = System::Drawing::Size(90, 24);
			this->btnDeleteWinding->TabIndex = 9;
			this->btnDeleteWinding->Text = L"Delete Winding";
			this->btnDeleteWinding->UseVisualStyleBackColor = true;
			this->btnDeleteWinding->Click += gcnew System::EventHandler(this, &Form1::btnDeleteWinding_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(11, 19);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(90, 23);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Add Section";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// txtWdgMVA
			// 
			this->txtWdgMVA->Location = System::Drawing::Point(250, 101);
			this->txtWdgMVA->Name = L"txtWdgMVA";
			this->txtWdgMVA->Size = System::Drawing::Size(75, 20);
			this->txtWdgMVA->TabIndex = 7;
			// 
			// cmbWdgConn
			// 
			this->cmbWdgConn->FormattingEnabled = true;
			this->cmbWdgConn->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Delta", L"Wye", L"Auto"});
			this->cmbWdgConn->Location = System::Drawing::Point(248, 71);
			this->cmbWdgConn->Name = L"cmbWdgConn";
			this->cmbWdgConn->Size = System::Drawing::Size(77, 21);
			this->cmbWdgConn->TabIndex = 6;
			// 
			// txtWdgVoltage
			// 
			this->txtWdgVoltage->Location = System::Drawing::Point(247, 43);
			this->txtWdgVoltage->Name = L"txtWdgVoltage";
			this->txtWdgVoltage->Size = System::Drawing::Size(79, 20);
			this->txtWdgVoltage->TabIndex = 5;
			// 
			// txtWdgName
			// 
			this->txtWdgName->Location = System::Drawing::Point(247, 16);
			this->txtWdgName->Name = L"txtWdgName";
			this->txtWdgName->Size = System::Drawing::Size(139, 20);
			this->txtWdgName->TabIndex = 4;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(154, 104);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(33, 13);
			this->label6->TabIndex = 3;
			this->label6->Text = L"MVA:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(154, 74);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(64, 13);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Connection:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(154, 46);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(46, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Voltage:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(154, 19);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(80, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Winding Name:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(145, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Transformer Name:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(175, 34);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"# of Phases:";
			// 
			// pnlTransformer
			// 
			this->pnlTransformer->Controls->Add(this->btnAddWinding);
			this->pnlTransformer->Controls->Add(this->txtLegRad);
			this->pnlTransformer->Controls->Add(this->label18);
			this->pnlTransformer->Controls->Add(this->txtMVA);
			this->pnlTransformer->Controls->Add(this->label17);
			this->pnlTransformer->Controls->Add(this->txtDistWdgTnk);
			this->pnlTransformer->Controls->Add(this->txtCoreWinHt);
			this->pnlTransformer->Controls->Add(this->label16);
			this->pnlTransformer->Controls->Add(this->label15);
			this->pnlTransformer->Controls->Add(this->opt3Ph);
			this->pnlTransformer->Controls->Add(this->opt1Ph);
			this->pnlTransformer->Controls->Add(this->txtXfmrName);
			this->pnlTransformer->Controls->Add(this->label2);
			this->pnlTransformer->Controls->Add(this->label1);
			this->pnlTransformer->Location = System::Drawing::Point(205, 39);
			this->pnlTransformer->Name = L"pnlTransformer";
			this->pnlTransformer->Size = System::Drawing::Size(397, 314);
			this->pnlTransformer->TabIndex = 2;
			// 
			// btnAddWinding
			// 
			this->btnAddWinding->Location = System::Drawing::Point(11, 10);
			this->btnAddWinding->Name = L"btnAddWinding";
			this->btnAddWinding->Size = System::Drawing::Size(90, 23);
			this->btnAddWinding->TabIndex = 13;
			this->btnAddWinding->Text = L"Add Winding";
			this->btnAddWinding->UseVisualStyleBackColor = true;
			this->btnAddWinding->Click += gcnew System::EventHandler(this, &Form1::btnAddWinding_Click);
			// 
			// txtLegRad
			// 
			this->txtLegRad->Location = System::Drawing::Point(253, 99);
			this->txtLegRad->Name = L"txtLegRad";
			this->txtLegRad->Size = System::Drawing::Size(74, 20);
			this->txtLegRad->TabIndex = 12;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(145, 102);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(97, 13);
			this->label18->TabIndex = 11;
			this->label18->Text = L"Active Leg Radius:";
			// 
			// txtMVA
			// 
			this->txtMVA->Location = System::Drawing::Point(253, 54);
			this->txtMVA->Name = L"txtMVA";
			this->txtMVA->Size = System::Drawing::Size(74, 20);
			this->txtMVA->TabIndex = 10;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(152, 57);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(90, 13);
			this->label17->TabIndex = 9;
			this->label17->Text = L"Self-Cooled MVA:";
			// 
			// txtDistWdgTnk
			// 
			this->txtDistWdgTnk->Location = System::Drawing::Point(253, 123);
			this->txtDistWdgTnk->Name = L"txtDistWdgTnk";
			this->txtDistWdgTnk->Size = System::Drawing::Size(74, 20);
			this->txtDistWdgTnk->TabIndex = 8;
			// 
			// txtCoreWinHt
			// 
			this->txtCoreWinHt->Location = System::Drawing::Point(253, 77);
			this->txtCoreWinHt->Name = L"txtCoreWinHt";
			this->txtCoreWinHt->Size = System::Drawing::Size(74, 20);
			this->txtCoreWinHt->TabIndex = 7;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(117, 126);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(125, 13);
			this->label16->TabIndex = 6;
			this->label16->Text = L"Distance, Winding-Tank:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(134, 80);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(108, 13);
			this->label15->TabIndex = 5;
			this->label15->Text = L"Core Window Height:";
			// 
			// opt3Ph
			// 
			this->opt3Ph->AutoSize = true;
			this->opt3Ph->Location = System::Drawing::Point(320, 32);
			this->opt3Ph->Name = L"opt3Ph";
			this->opt3Ph->Size = System::Drawing::Size(53, 17);
			this->opt3Ph->TabIndex = 4;
			this->opt3Ph->TabStop = true;
			this->opt3Ph->Text = L"Three";
			this->opt3Ph->UseVisualStyleBackColor = true;
			// 
			// opt1Ph
			// 
			this->opt1Ph->AutoSize = true;
			this->opt1Ph->Checked = true;
			this->opt1Ph->Location = System::Drawing::Point(261, 32);
			this->opt1Ph->Name = L"opt1Ph";
			this->opt1Ph->Size = System::Drawing::Size(54, 17);
			this->opt1Ph->TabIndex = 3;
			this->opt1Ph->TabStop = true;
			this->opt1Ph->Text = L"Single";
			this->opt1Ph->UseVisualStyleBackColor = true;
			// 
			// txtXfmrName
			// 
			this->txtXfmrName->Location = System::Drawing::Point(253, 8);
			this->txtXfmrName->Name = L"txtXfmrName";
			this->txtXfmrName->Size = System::Drawing::Size(120, 20);
			this->txtXfmrName->TabIndex = 2;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->runToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(617, 24);
			this->menuStrip1->TabIndex = 8;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->newToolStripMenuItem, 
				this->openToolStripMenuItem, this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->toolStripSeparator1, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->newToolStripMenuItem->Text = L"New";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->openToolStripMenuItem->Text = L"Open...";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As...";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveAsToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(120, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(123, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// runToolStripMenuItem
			// 
			this->runToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->writeGMSHFileToolStripMenuItem, 
				this->showPlotToolStripMenuItem, this->showConsoleToolStripMenuItem});
			this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
			this->runToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->runToolStripMenuItem->Text = L"Run";
			// 
			// writeGMSHFileToolStripMenuItem
			// 
			this->writeGMSHFileToolStripMenuItem->Name = L"writeGMSHFileToolStripMenuItem";
			this->writeGMSHFileToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->writeGMSHFileToolStripMenuItem->Text = L"Run the Sumbitch";
			this->writeGMSHFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::writeGMSHFileToolStripMenuItem_Click);
			// 
			// showPlotToolStripMenuItem
			// 
			this->showPlotToolStripMenuItem->Name = L"showPlotToolStripMenuItem";
			this->showPlotToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->showPlotToolStripMenuItem->Text = L"Show Plot";
			this->showPlotToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::showPlotToolStripMenuItem_Click);
			// 
			// showConsoleToolStripMenuItem
			// 
			this->showConsoleToolStripMenuItem->Name = L"showConsoleToolStripMenuItem";
			this->showConsoleToolStripMenuItem->Size = System::Drawing::Size(169, 22);
			this->showConsoleToolStripMenuItem->Text = L"Show Console";
			this->showConsoleToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::showConsoleToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->aboutToolStripMenuItem, 
				this->contentsToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// contentsToolStripMenuItem
			// 
			this->contentsToolStripMenuItem->Name = L"contentsToolStripMenuItem";
			this->contentsToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->contentsToolStripMenuItem->Text = L"Contents";
			// 
			// pnlSection
			// 
			this->pnlSection->Controls->Add(this->txtSecName);
			this->pnlSection->Controls->Add(this->label14);
			this->pnlSection->Controls->Add(this->txtStdsPerTrn);
			this->pnlSection->Controls->Add(this->txtTurnsAxi);
			this->pnlSection->Controls->Add(this->txtTurnsRad);
			this->pnlSection->Controls->Add(this->txtHtAbvYoke);
			this->pnlSection->Controls->Add(this->txtHeight);
			this->pnlSection->Controls->Add(this->txtOuterRad);
			this->pnlSection->Controls->Add(this->txtInnerRad);
			this->pnlSection->Controls->Add(this->label13);
			this->pnlSection->Controls->Add(this->label12);
			this->pnlSection->Controls->Add(this->label11);
			this->pnlSection->Controls->Add(this->label10);
			this->pnlSection->Controls->Add(this->label9);
			this->pnlSection->Controls->Add(this->label8);
			this->pnlSection->Controls->Add(this->label7);
			this->pnlSection->Location = System::Drawing::Point(205, 38);
			this->pnlSection->Name = L"pnlSection";
			this->pnlSection->Size = System::Drawing::Size(394, 319);
			this->pnlSection->TabIndex = 9;
			// 
			// txtSecName
			// 
			this->txtSecName->Location = System::Drawing::Point(281, 17);
			this->txtSecName->Name = L"txtSecName";
			this->txtSecName->Size = System::Drawing::Size(93, 20);
			this->txtSecName->TabIndex = 15;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(174, 20);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(77, 13);
			this->label14->TabIndex = 14;
			this->label14->Text = L"Section Name:";
			// 
			// txtStdsPerTrn
			// 
			this->txtStdsPerTrn->Location = System::Drawing::Point(281, 212);
			this->txtStdsPerTrn->Name = L"txtStdsPerTrn";
			this->txtStdsPerTrn->Size = System::Drawing::Size(93, 20);
			this->txtStdsPerTrn->TabIndex = 13;
			// 
			// txtTurnsAxi
			// 
			this->txtTurnsAxi->Location = System::Drawing::Point(281, 184);
			this->txtTurnsAxi->Name = L"txtTurnsAxi";
			this->txtTurnsAxi->Size = System::Drawing::Size(93, 20);
			this->txtTurnsAxi->TabIndex = 12;
			// 
			// txtTurnsRad
			// 
			this->txtTurnsRad->Location = System::Drawing::Point(281, 156);
			this->txtTurnsRad->Name = L"txtTurnsRad";
			this->txtTurnsRad->Size = System::Drawing::Size(93, 20);
			this->txtTurnsRad->TabIndex = 11;
			// 
			// txtHtAbvYoke
			// 
			this->txtHtAbvYoke->Location = System::Drawing::Point(281, 128);
			this->txtHtAbvYoke->Name = L"txtHtAbvYoke";
			this->txtHtAbvYoke->Size = System::Drawing::Size(93, 20);
			this->txtHtAbvYoke->TabIndex = 10;
			// 
			// txtHeight
			// 
			this->txtHeight->Location = System::Drawing::Point(281, 100);
			this->txtHeight->Name = L"txtHeight";
			this->txtHeight->Size = System::Drawing::Size(93, 20);
			this->txtHeight->TabIndex = 9;
			// 
			// txtOuterRad
			// 
			this->txtOuterRad->Location = System::Drawing::Point(281, 72);
			this->txtOuterRad->Name = L"txtOuterRad";
			this->txtOuterRad->Size = System::Drawing::Size(93, 20);
			this->txtOuterRad->TabIndex = 8;
			// 
			// txtInnerRad
			// 
			this->txtInnerRad->Location = System::Drawing::Point(281, 44);
			this->txtInnerRad->Name = L"txtInnerRad";
			this->txtInnerRad->Size = System::Drawing::Size(93, 20);
			this->txtInnerRad->TabIndex = 7;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(175, 215);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(73, 13);
			this->label13->TabIndex = 6;
			this->label13->Text = L"Strands/Turn:";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(175, 187);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(82, 13);
			this->label12->TabIndex = 5;
			this->label12->Text = L"# Turns, Axially:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(175, 159);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(90, 13);
			this->label11->TabIndex = 4;
			this->label11->Text = L"# Turns, Radially:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(175, 103);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(41, 13);
			this->label10->TabIndex = 3;
			this->label10->Text = L"Height:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(175, 131);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(103, 13);
			this->label9->TabIndex = 2;
			this->label9->Text = L"Height Above Yoke:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(175, 75);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(72, 13);
			this->label8->TabIndex = 1;
			this->label8->Text = L"Outer Radius:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(175, 47);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(70, 13);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Inner Radius:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton3);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(214, 360);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(135, 34);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Formulation";
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(98, 11);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(31, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->Text = L"3";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(61, 11);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(31, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->Text = L"2";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(18, 11);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(31, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"1";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->radioButton5);
			this->groupBox2->Controls->Add(this->radioButton4);
			this->groupBox2->Location = System::Drawing::Point(369, 360);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(221, 33);
			this->groupBox2->TabIndex = 11;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Element Order";
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(76, 11);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(43, 17);
			this->radioButton5->TabIndex = 1;
			this->radioButton5->Text = L"2nd";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Checked = true;
			this->radioButton4->Location = System::Drawing::Point(13, 11);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(39, 17);
			this->radioButton4->TabIndex = 0;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"1st";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(617, 398);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->treeTfmr);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->pnlSection);
			this->Controls->Add(this->pnlTransformer);
			this->Controls->Add(this->pnlWinding);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->pnlWinding->ResumeLayout(false);
			this->pnlWinding->PerformLayout();
			this->pnlTransformer->ResumeLayout(false);
			this->pnlTransformer->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->pnlSection->ResumeLayout(false);
			this->pnlSection->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
    private: System::Void btnAddWinding_Click(System::Object^  sender, System::EventArgs^  e) {
				 Winding^ newWinding = transformer->addWinding();
				 TreeNode^ newNode = gcnew TreeNode("Winding");
				 newNode->Tag = newWinding;
				 treeTfmr->Nodes["Transformer"]->Nodes->Add(newNode);
				 newNode->Parent->ExpandAll();
			 }
		
			 System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
				TreeNode^ selectedNode = treeTfmr->SelectedNode;
				Winding^ selectedWinding = safe_cast<Winding^> (selectedNode->Tag);
				Section^ newSection = selectedWinding->addSection();
				TreeNode^ newNode = gcnew TreeNode("Section");
				newNode->Tag = newSection;
				selectedNode->Nodes->Add(newNode);
				newNode->Parent->ExpandAll();
			 }

			 System::Void refreshTree(){
				 treeTfmr->Nodes->Clear();
				 TreeNode^ newXfmrNode = gcnew TreeNode(transformer->name);
				 treeTfmr->Nodes->Add(newXfmrNode);
				 for each (Winding^ wdg in transformer->windings){
					 TreeNode^ newWdgNode = gcnew TreeNode(wdg->name);
					 newWdgNode->Tag = wdg;
					 newXfmrNode->Nodes->Add(newWdgNode);
					 for each (Section^ sect in wdg->sections){
						 TreeNode^ newSectNode = gcnew TreeNode(sect->name);
						 newSectNode->Tag = sect;
						 newWdgNode->Nodes->Add(newSectNode);
					 }
				 }
				 treeTfmr->ExpandAll();
			 }

		   System::Void showWinding(Winding^ wdg){
			  pnlTransformer->Visible = false;
			  pnlWinding->Visible = true;
			  pnlSection->Visible = false;
			  txtWdgName->Text = wdg->name;
			  txtWdgVoltage->Text = Convert::ToString(wdg->voltage);
			  cmbWdgConn->Text = wdg->connection;
			  txtWdgMVA->Text = Convert::ToString(wdg->MVA);
			  if(wdg->currDir == -1){
				  optCurrentNeg->Checked = true;
			  } else if(wdg->currDir == 1){
				  optCurrentPos->Checked = true;
			  } else {
				  //error
			  }
		   }

		   System::Void showSection(Section^ section){
			  pnlTransformer->Visible = false;
			  pnlWinding->Visible = false;
			  pnlSection->Visible = true;
			  txtSecName->Text = section->name;
			  txtInnerRad->Text = Convert::ToString(section->radius_inner);
			  txtOuterRad->Text = Convert::ToString(section->radius_outer);
			  txtHeight->Text = Convert::ToString(section->height);
			  txtHtAbvYoke->Text = Convert::ToString(section->h_abv_yoke);
			  txtTurnsRad->Text = Convert::ToString(section->turns_rad);
			  txtTurnsAxi->Text = Convert::ToString(section->turns_axi);
			  txtStdsPerTrn->Text = Convert::ToString(section->strands_per_turn);
		   }

		   System::Void showTransformer(){
			  pnlTransformer->Visible = true;
			  pnlWinding->Visible = false;
			  pnlSection->Visible = false;
			  txtXfmrName->Text = transformer->name;
			  txtCoreWinHt->Text = Convert::ToString(transformer->core->window_height);
			  txtLegRad->Text = Convert::ToString(transformer->core->radius_leg);
			  txtDistWdgTnk->Text = Convert::ToString(transformer->dist_WdgTnk);
			  if(transformer->numPhases==1){
				  opt1Ph->Checked=true;
			  }else if(transformer->numPhases==3){
				  opt3Ph->Checked=true;
			  }else{
				  //throw error
			  }
		   }

		   System::Void getWinding(Winding^ wdg){
			   wdg->name = txtWdgName->Text;
			   wdg->voltage = Convert::ToDouble(txtWdgVoltage->Text);
			   wdg->connection = cmbWdgConn->Text;
			   wdg->MVA = Convert::ToDouble(txtWdgMVA->Text);
			   if(optCurrentNeg->Checked){
				   wdg->currDir = -1;
			   }else{
				   wdg->currDir = 1;
			   }
		   }

		   System::Void getSection(Section^ section){
			   section->name = txtSecName->Text;
			   section->radius_inner = Convert::ToDouble(txtInnerRad->Text);
			   section->radius_outer = Convert::ToDouble(txtOuterRad->Text);
			   section->height = Convert::ToDouble(txtHeight->Text);
			   section->h_abv_yoke = Convert::ToDouble(txtHtAbvYoke->Text);
			   section->turns_rad = Convert::ToInt32(txtTurnsRad->Text);
			   section->turns_axi = Convert::ToInt32(txtTurnsAxi->Text);
			   section->strands_per_turn = Convert::ToInt32(txtStdsPerTrn->Text);
		   }

		   System::Void getTransformer(){
			   transformer->name = txtXfmrName->Text;
			   transformer->core->window_height = Convert::ToDouble(txtCoreWinHt->Text);
			   transformer->core->radius_leg = Convert::ToDouble(txtLegRad->Text);
			   transformer->dist_WdgTnk = Convert::ToDouble(txtDistWdgTnk->Text);
			   if(opt1Ph->Checked){
				   transformer->numPhases=1;
			   }else{
				   transformer->numPhases=3;
			   }
		   }

private: System::Void treeTfmr_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 if(treeTfmr->SelectedNode->Level == 0){
				 showTransformer();
			 } else if(treeTfmr->SelectedNode->Level == 1){
				 showWinding(dynamic_cast<Winding^>(treeTfmr->SelectedNode->Tag));
			 } else if(treeTfmr->SelectedNode->Level == 2){
				 showSection(dynamic_cast<Section^>(treeTfmr->SelectedNode->Tag));
			 } else {
				 //error
			 }
		 }

private: System::Void treeTfmr_BeforeSelect(System::Object^  sender, System::Windows::Forms::TreeViewCancelEventArgs^  e) {
			 if(treeTfmr->SelectedNode != nullptr){
				 if(treeTfmr->SelectedNode->Level == 0){
					 getTransformer();
				 } else if(treeTfmr->SelectedNode->Level == 1){
					 getWinding(dynamic_cast<Winding^>(treeTfmr->SelectedNode->Tag));
				 } else if(treeTfmr->SelectedNode->Level == 2){
					 getSection(dynamic_cast<Section^>(treeTfmr->SelectedNode->Tag));
				 } else {
					 //error
				 }
			 }
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Application::Exit();
		 }
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 if(tdapFileName == ""){

				SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
			 
				saveFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
				saveFileDialog1->FilterIndex = 2;
				saveFileDialog1->RestoreDirectory = true;

				if ( saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
				{
					tdapFileName = saveFileDialog1->FileName;
					saveFile();
				}
			 } else {
				 saveFile();
			 }
		 }

private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 

			 SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
			 
			 saveFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
			 saveFileDialog1->FilterIndex = 2;
			 saveFileDialog1->RestoreDirectory = true;

			 if ( saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			 {
				 tdapFileName = saveFileDialog1->FileName;
				 saveFile();
			 }
		 }

		 System::Void saveFile(){
			 // Create an instance of the XmlSerializer class;
			 // specify the type of object to serialize.
			 if(treeTfmr->SelectedNode != nullptr){
				 if(treeTfmr->SelectedNode->Level == 0){
					 getTransformer();
				 } else if(treeTfmr->SelectedNode->Level == 1){
					 getWinding(dynamic_cast<Winding^>(treeTfmr->SelectedNode->Tag));
				 } else if(treeTfmr->SelectedNode->Level == 2){
					 getSection(dynamic_cast<Section^>(treeTfmr->SelectedNode->Tag));
				 } else {
					 //error
				 }
			 }
			 XmlSerializer^ serializer = gcnew XmlSerializer(Transformer::typeid);
			 TextWriter^ writer = gcnew StreamWriter(tdapFileName);
			 // Serialize the purchase order, and close the TextWriter.
			 serializer->Serialize(writer, transformer);
			 writer->Close();
		 }


private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			 Stream^ fs;

			 //openFileDialog1->InitialDirectory = "c:\\";
			 openFileDialog1->Filter = "xml files (*.xml)|*.xml|All files (*.*)|*.*";
			 openFileDialog1->FilterIndex = 2;
			 openFileDialog1->RestoreDirectory = true;

			 if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			 {
			    tdapFileName = openFileDialog1->FileName;
				if ( (fs = openFileDialog1->OpenFile()) != nullptr )
				{
					  // Create an instance of the XmlSerializer class;
					  // specify the type of object to be deserialized.
					  XmlSerializer^ serializer = gcnew XmlSerializer(Transformer::typeid);
					  /* If the XML document has been altered with unknown 
					  nodes or attributes, handle them with the 
					  UnknownNode and UnknownAttribute events.*/
					  //serializer->UnknownNode += gcnew XmlNodeEventHandler( this, &serializer_UnknownNode );
					  //serializer->UnknownAttribute += gcnew XmlAttributeEventHandler( this, &serializer_UnknownAttribute );
		   
					  // A FileStream is needed to read the XML document.
					  //FileStream^ fs = gcnew FileStream(Application::StartupPath + "\\test.xml", FileMode::Open);
					  
					  /* Use the Deserialize method to restore the object's state with
					  data from the XML document. */
					  transformer = dynamic_cast<Transformer^>(serializer->Deserialize(fs));
					  fs->Close();
					  deserializer_RestorePointers();
					  refreshTree();
				}
			 }
		 }

		 //The following must be called after "deserializing" the transformer from the file
		 //to restore the pointers back to the "parent" objects.
		 void deserializer_RestorePointers(){
			 for each (Winding^ winding in transformer->windings){
				 winding->transformer = transformer;
				 for each (Section^ section in winding->sections){
					 section->winding = winding;
				 }
			 }
		 }

		 void serializer_UnknownNode( Object^ /*sender*/, XmlNodeEventArgs^ e )
		   {
			  Console::WriteLine( "Unknown Node:{0}\t{1}", e->Name, e->Text );
		   }

		   void serializer_UnknownAttribute( Object^ /*sender*/, XmlAttributeEventArgs^ e )
		   {
			  System::Xml::XmlAttribute^ attr = e->Attr;
			  Console::WriteLine( "Unknown attribute {0}='{1}'", attr->Name, attr->Value );
		   }

private: System::Void writeGMSHFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ tdapFileRoot = tdapFileName->Remove(tdapFileName->Length-4);
			 if(radioButton1->Checked==true){
				 transformer->formulation=0;
			 }else if(radioButton2->Checked==true){
				 transformer->formulation=1;
			 }else if(radioButton3->Checked==true){
				 transformer->formulation=2;
			 }else{
				 transformer->formulation=0;
			 }
			 if(radioButton4->Checked==true){
				transformer->ElementOrder=1;
			 }else if(radioButton5->Checked==true){
				 transformer->ElementOrder=2;
			 }else{
				 transformer->ElementOrder=1;
			 }

			 Stopwatch^ stopWatch;
			 stopWatch = gcnew Stopwatch;

			 stopWatch->Start();

			 transformer->writeTransformerGmsh(tdapFileRoot + ".geo");
			 transformer->writeAttributes(tdapFileRoot + ".att");
			 generateMesh(tdapFileRoot);
			 runFEAnalysis(tdapFileRoot);

			 stopWatch->Stop();
			 int runTime = stopWatch->ElapsedMilliseconds;
			 MessageBox::Show( "Run Time (ms) = " + runTime, "Run Time",
            MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
			 MessageBox::Show( "X_pu=" + transformer->X_pu, "Impedance",
            MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
			 
		 }
private: System::Void generateMesh(String^ tdapFileRoot) {
			 try{
				 System::Diagnostics::Process^ meshProcess = gcnew System::Diagnostics::Process();
				 meshProcess->StartInfo->FileName = String::Concat(Application::StartupPath, "\\gmsh.exe");
				 meshProcess->StartInfo->WorkingDirectory = Application::StartupPath;
				 //myProcess->StartInfo->CreateNoWindow = true;
				 //meshProcess->StartInfo->RedirectStandardOutput = true;
				 //meshProcess->StartInfo->UseShellExecute = false;
				 meshProcess->StartInfo->Arguments = "\"" + tdapFileRoot + ".geo\" -2"; //String::Concat(Application::StartupPath, "\\test.geo -2");// -o ", Application::StartupPath, "\\test.msh");
				 //meshProcess->StartInfo->Arguments = "-info";
				 meshProcess->Start();
				 meshProcess->WaitForExit();
				 //Console::WriteLine(meshProcess->StandardOutput->ReadToEnd());
				 //richTextBox1->LoadFile(meshProcess->StandardOutput->BaseStream, RichTextBoxStreamType::PlainText);
				 
				 //ShellExecute ( NULL, "open", Application::StartupPath + "\\gmsh.exe", "test.geo -2", NULL, SW_SHOWNORMAL );
			 }
			 catch ( Win32Exception^ e ) {
		        Console::WriteLine( "{0}", e->Message );
			 }
		}

private: System::Void runFEAnalysis(String^ tdapFileRoot) {
			 frmConsole^ console = gcnew frmConsole();
			 console->Show();

			 transformer->setFilename(tdapFileRoot);
			 Process^ processCurrent = Process::GetCurrentProcess();
			 TimeSpan^ startTime = processCurrent->TotalProcessorTime;
			 transformer->runFEA();
			 //ThreadStart^ threadDelegate = gcnew ThreadStart( transformer, &Transformer::runFEA );
			 //Thread^ newThread = gcnew Thread( threadDelegate );
			 //newThread->Start();
			 //while (newThread->IsAlive){
			     //console->setText( &(transformer->getStream()->str()) );
			//	 console->Refresh();
			//	 Thread::Sleep(1000);
			 //}
			 double stopTime = Process::GetCurrentProcess()->TotalProcessorTime.Milliseconds - startTime->Milliseconds;
			 //MessageBox::Show( "Run Time minus X calc (ms) = " + stopTime, "Run Time",
			//	MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
//			 console->setText( &(transformer->getStream()->str()) );
		     console->Refresh();

			 //transformer->runFEA(tdapFileRoot);
			 transformer->calcX();
		 }
private: System::Void showPlotToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 transformer->contourPlot();
		 }
private: System::Void showConsoleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 frmConsole^ console = gcnew frmConsole();
			 console->Show();
		 }

private: System::Void btnDeleteWinding_Click(System::Object^  sender, System::EventArgs^  e) {
			 transformer->deleteWinding(dynamic_cast<Winding^>(treeTfmr->SelectedNode->Tag));
			 refreshTree();
		 }
};

}