#pragma once
namespace LabsMenu {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;


	/// <summary>
	/// —водка дл€ LabsMenu
	/// </summary>
	public ref class LabsMenu : public System::Windows::Forms::Form
	{
	public:
		LabsMenu(void)
		{
			InitializeComponent();

			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~LabsMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ button13;
	private: System::Windows::Forms::Button^ button14;
	private: System::Windows::Forms::Button^ button15;
	private: System::Windows::Forms::Button^ button16;

	protected:

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LabsMenu::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button1->Name = L"button1";
			this->button1->TabIndex = 0;
			this->button1->Text = L"Input / Output";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &LabsMenu::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button2->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button2->Name = L"button2";
			this->button2->TabIndex = 1;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &LabsMenu::button2_Click);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button3->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button3->Name = L"button3";
			this->button3->TabIndex = 2;
			this->button3->Text = L"Lab3";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &LabsMenu::button3_Click);
			// 
			// button4
			// 
			this->button4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button4->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button4->Name = L"button4";
			this->button4->TabIndex = 3;
			this->button4->Text = L"Lab4";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &LabsMenu::button4_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button5->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button5->Name = L"button5";
			this->button5->TabIndex = 5;
			this->button5->Text = L"Lab5";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &LabsMenu::button5_Click);
			// 
			// button6
			// 
			this->button6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button6->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button6->Name = L"button6";
			this->button6->TabIndex = 6;
			this->button6->Text = L"Lab6";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &LabsMenu::button6_Click);
			// 
			// button7
			// 
			this->button7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button7->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button7->Name = L"button7";
			this->button7->TabIndex = 7;
			this->button7->Text = L"Lab7";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &LabsMenu::button7_Click);
			// 
			// button8
			// 
			this->button8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button8->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button8->Location = System::Drawing::Point(31, 387);
			this->button8->Margin = System::Windows::Forms::Padding(8);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(198, 41);
			this->button8->TabIndex = 14;
			this->button8->Text = L"Templates";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &LabsMenu::button8_Click);
			// 
			// button9
			// 
			this->button9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button9->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.8F));
			this->button9->Location = System::Drawing::Point(31, 330);
			this->button9->Margin = System::Windows::Forms::Padding(8);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(198, 41);
			this->button9->TabIndex = 13;
			this->button9->Text = L"Virtual Inheritance";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &LabsMenu::button9_Click);
			// 
			// button10
			// 
			this->button10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button10->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button10->Location = System::Drawing::Point(31, 273);
			this->button10->Margin = System::Windows::Forms::Padding(8);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(198, 41);
			this->button10->TabIndex = 12;
			this->button10->Text = L"Polymorphism";
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &LabsMenu::button10_Click);
			// 
			// button11
			// 
			this->button11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button11->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button11->Location = System::Drawing::Point(31, 216);
			this->button11->Margin = System::Windows::Forms::Padding(8);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(198, 41);
			this->button11->TabIndex = 11;
			this->button11->Text = L"Inheritance";
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &LabsMenu::button11_Click);
			// 
			// button12
			// 
			this->button12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button12->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button12->Location = System::Drawing::Point(31, 159);
			this->button12->Margin = System::Windows::Forms::Padding(8);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(198, 41);
			this->button12->TabIndex = 10;
			this->button12->Text = L"Friend Functions";
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &LabsMenu::button12_Click);
			// 
			// button13
			// 
			this->button13->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button13->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button13->Location = System::Drawing::Point(31, 102);
			this->button13->Margin = System::Windows::Forms::Padding(8);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(198, 41);
			this->button13->TabIndex = 9;
			this->button13->Text = L"Dynamic memory";
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &LabsMenu::button13_Click);
			// 
			// button14
			// 
			this->button14->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button14->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button14->Location = System::Drawing::Point(31, 46);
			this->button14->Margin = System::Windows::Forms::Padding(8);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(198, 41);
			this->button14->TabIndex = 8;
			this->button14->Text = L"Queue";
			this->button14->UseVisualStyleBackColor = false;
			this->button14->Click += gcnew System::EventHandler(this, &LabsMenu::button14_Click);
			// 
			// button15
			// 
			this->button15->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button15->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button15->Location = System::Drawing::Point(31, 444);
			this->button15->Margin = System::Windows::Forms::Padding(8);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(198, 41);
			this->button15->TabIndex = 15;
			this->button15->Text = L"Smart pointers";
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &LabsMenu::button15_Click);
			// 
			// button16
			// 
			this->button16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button16->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button16->Location = System::Drawing::Point(31, 500);
			this->button16->Margin = System::Windows::Forms::Padding(8);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(198, 41);
			this->button16->TabIndex = 16;
			this->button16->Text = L"Exceptions";
			this->button16->UseVisualStyleBackColor = false;
			this->button16->Click += gcnew System::EventHandler(this, &LabsMenu::button16_Click);
			// 
			// LabsMenu
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"LabsMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"LabsMenu";
			this->Load += gcnew System::EventHandler(this, &LabsMenu::LabsMenu_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void LabsMenu_Load(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Process::Start("D:/University/OOPIP/OOPIP2/x64/Debug/IOStreams_1.exe");
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab5.exe");
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button15_Click(System::Object^ sender, System::EventArgs^ e) {
		Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/CourseProject.exe");
	}
	private: System::Void button14_Click(System::Object^ sender, System::EventArgs^ e) {
		OOPIPMolchanM::Lab1^ form = gcnew OOPIPMolchanM::Lab1();
		System::Drawing::Point location = this->DesktopLocation;
		this->Hide();

		form->DesktopLocation = location;

		form->ShowDialog();
		this->DesktopLocation = form->DesktopLocation;
		this->Show();
	}
private: System::Void button13_Click(System::Object^ sender, System::EventArgs^ e) {
	Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab2.exe");
}
private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e) {
	Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab3.exe");
}
private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e) {
	OOPIPMolchanM::lab4^ form = gcnew OOPIPMolchanM::lab4();
	System::Drawing::Point location = this->DesktopLocation;
	this->Hide();

	form->DesktopLocation = location;

	form->ShowDialog();
	this->DesktopLocation = form->DesktopLocation;
	this->Show();
}
private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
	Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab5.exe");
}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
	Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab6.exe");
}
private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
	Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab7.exe");
}
private: System::Void button16_Click(System::Object^ sender, System::EventArgs^ e) {
	Process::Start("D:/University/OOPIP/OOPIP_MolchanM/x64/Debug/Lab9.exe");
}
	};
}
