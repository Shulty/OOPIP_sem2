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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button1->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button1->Location = System::Drawing::Point(427, 19);
			this->button1->Margin = System::Windows::Forms::Padding(10);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(264, 50);
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
			this->button2->Location = System::Drawing::Point(427, 89);
			this->button2->Margin = System::Windows::Forms::Padding(10);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(264, 50);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Lab2";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &LabsMenu::button2_Click);
			// 
			// button3
			// 
			this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button3->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button3->Location = System::Drawing::Point(427, 159);
			this->button3->Margin = System::Windows::Forms::Padding(10);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(264, 50);
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
			this->button4->Location = System::Drawing::Point(427, 229);
			this->button4->Margin = System::Windows::Forms::Padding(10);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(264, 50);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Lab4";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &LabsMenu::button4_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(-13, -32);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(728, 810);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// button5
			// 
			this->button5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button5->BackColor = System::Drawing::Color::MediumTurquoise;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.8F));
			this->button5->Location = System::Drawing::Point(427, 299);
			this->button5->Margin = System::Windows::Forms::Padding(10);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(264, 50);
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
			this->button6->Location = System::Drawing::Point(427, 369);
			this->button6->Margin = System::Windows::Forms::Padding(10);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(264, 50);
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
			this->button7->Location = System::Drawing::Point(427, 439);
			this->button7->Margin = System::Windows::Forms::Padding(10);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(264, 50);
			this->button7->TabIndex = 7;
			this->button7->Text = L"Lab7";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &LabsMenu::button7_Click);
			// 
			// LabsMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(710, 763);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
	};
}
