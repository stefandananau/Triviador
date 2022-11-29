#pragma once
#include <winsock2.h>
#include <msclr/marshal_cppstd.h>

#undef _M_CEE
#include "../clientTriviador/LoginRegister.h"
#define _M_CEE

namespace TriviadorGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LoginRegisterWindow
	/// </summary>
	public ref class LoginRegisterWindow : public System::Windows::Forms::Form
	{
		
	public:
		LoginRegisterWindow(void)
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
		~LoginRegisterWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RichTextBox^ ClientHelperOutput;

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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->ClientHelperOutput = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(109, 61);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(138, 26);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 65);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Email";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(27, 112);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(78, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Password";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(109, 109);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(138, 26);
			this->textBox2->TabIndex = 3;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(31, 211);
			this->button1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(84, 29);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Login";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(163, 211);
			this->button2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(84, 29);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Register";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &LoginRegisterWindow::registerButton_Click);
			// 
			// ClientHelperOutput
			// 
			this->ClientHelperOutput->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->ClientHelperOutput->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->ClientHelperOutput->Location = System::Drawing::Point(31, 155);
			this->ClientHelperOutput->Name = L"ClientHelperOutput";
			this->ClientHelperOutput->Size = System::Drawing::Size(216, 38);
			this->ClientHelperOutput->TabIndex = 6;
			this->ClientHelperOutput->Text = L"";
			this->ClientHelperOutput->TextChanged += gcnew System::EventHandler(this, &LoginRegisterWindow::ClientHelperOutput_TextChanged);
			// 
			// LoginRegisterWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(304, 278);
			this->Controls->Add(this->ClientHelperOutput);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"LoginRegisterWindow";
			this->Text = L"LoginRegisterWindow";
			this->Load += gcnew System::EventHandler(this, &LoginRegisterWindow::LoginRegisterWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void LoginRegisterWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		msclr::interop::marshal_context context;
		std::string email = context.marshal_as<std::string>(textBox1->Text);
		std::string password = context.marshal_as<std::string>(textBox2->Text);

		ClientHelperOutput->Text = gcnew String(ClientHelper::loginUser(email, password).c_str());
	}
	
	private: System::Void registerButton_Click(System::Object^ sender, System::EventArgs^ e) {
		msclr::interop::marshal_context context;
		std::string email = context.marshal_as<std::string>(textBox1->Text);
		std::string password = context.marshal_as<std::string>(textBox2->Text);

		ClientHelperOutput->Text = gcnew String(ClientHelper::registerUser(email, password).c_str());
	}
private: System::Void ClientHelperOutput_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
