#pragma once

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
			// LoginRegisterWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(653, 501);
			this->Name = L"LoginRegisterWindow";
			this->Text = L"LoginRegisterWindow";
			this->Load += gcnew System::EventHandler(this, &LoginRegisterWindow::LoginRegisterWindow_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void LoginRegisterWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
