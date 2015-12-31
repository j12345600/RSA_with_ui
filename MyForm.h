#pragma once
#include  "RSA_util.h"
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal.h>

namespace RSA_with_UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		RSA_util *rsa;
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox_input;
	private: System::Windows::Forms::ListBox^  RSA;
	private: System::Windows::Forms::ComboBox^  comboBoxModeSelc;
	private: System::Windows::Forms::TextBox^  textBoxUserInput;
	private: System::Windows::Forms::Button^  buttEncryption;
	private: System::Windows::Forms::Button^  buttDecryption;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label_time_elapsed;
	private: System::Windows::Forms::Button^  buttonDecrypt_with_CRT;





	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox_input = (gcnew System::Windows::Forms::TextBox());
			this->RSA = (gcnew System::Windows::Forms::ListBox());
			this->comboBoxModeSelc = (gcnew System::Windows::Forms::ComboBox());
			this->textBoxUserInput = (gcnew System::Windows::Forms::TextBox());
			this->buttEncryption = (gcnew System::Windows::Forms::Button());
			this->buttDecryption = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label_time_elapsed = (gcnew System::Windows::Forms::Label());
			this->buttonDecrypt_with_CRT = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(630, 259);
			this->button1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(217, 64);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Generate key pair";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox_input
			// 
			this->textBox_input->Location = System::Drawing::Point(390, 340);
			this->textBox_input->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->textBox_input->Multiline = true;
			this->textBox_input->Name = L"textBox_input";
			this->textBox_input->Size = System::Drawing::Size(457, 302);
			this->textBox_input->TabIndex = 1;
			// 
			// RSA
			// 
			this->RSA->FormattingEnabled = true;
			this->RSA->ItemHeight = 18;
			this->RSA->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"P", L"Q", L"N", L"Public key", L"Private key" });
			this->RSA->Location = System::Drawing::Point(707, 25);
			this->RSA->Name = L"RSA";
			this->RSA->Size = System::Drawing::Size(123, 112);
			this->RSA->TabIndex = 2;
			this->RSA->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::RSA_SelectedIndexChanged);
			// 
			// comboBoxModeSelc
			// 
			this->comboBoxModeSelc->FormattingEnabled = true;
			this->comboBoxModeSelc->ImeMode = System::Windows::Forms::ImeMode::Disable;
			this->comboBoxModeSelc->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"4096 bits", L"2048 bits", L"1024 bits",
					L"512 bits"
			});
			this->comboBoxModeSelc->Location = System::Drawing::Point(707, 143);
			this->comboBoxModeSelc->Name = L"comboBoxModeSelc";
			this->comboBoxModeSelc->Size = System::Drawing::Size(121, 26);
			this->comboBoxModeSelc->TabIndex = 3;
			// 
			// textBoxUserInput
			// 
			this->textBoxUserInput->Location = System::Drawing::Point(30, 95);
			this->textBoxUserInput->Multiline = true;
			this->textBoxUserInput->Name = L"textBoxUserInput";
			this->textBoxUserInput->Size = System::Drawing::Size(265, 177);
			this->textBoxUserInput->TabIndex = 4;
			// 
			// buttEncryption
			// 
			this->buttEncryption->Location = System::Drawing::Point(53, 287);
			this->buttEncryption->Name = L"buttEncryption";
			this->buttEncryption->Size = System::Drawing::Size(108, 58);
			this->buttEncryption->TabIndex = 5;
			this->buttEncryption->Text = L"Encrypt";
			this->buttEncryption->UseVisualStyleBackColor = true;
			this->buttEncryption->Click += gcnew System::EventHandler(this, &MyForm::buttEncryption_Click);
			// 
			// buttDecryption
			// 
			this->buttDecryption->Location = System::Drawing::Point(167, 287);
			this->buttDecryption->Name = L"buttDecryption";
			this->buttDecryption->Size = System::Drawing::Size(109, 58);
			this->buttDecryption->TabIndex = 6;
			this->buttDecryption->Text = L"Decrypt";
			this->buttDecryption->UseVisualStyleBackColor = true;
			this->buttDecryption->Click += gcnew System::EventHandler(this, &MyForm::buttDecryption_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(386, 287);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(199, 24);
			this->label1->TabIndex = 7;
			this->label1->Text = L"RSA status: NULL";
			// 
			// label_time_elapsed
			// 
			this->label_time_elapsed->AutoSize = true;
			this->label_time_elapsed->Location = System::Drawing::Point(387, 215);
			this->label_time_elapsed->Name = L"label_time_elapsed";
			this->label_time_elapsed->Size = System::Drawing::Size(0, 18);
			this->label_time_elapsed->TabIndex = 8;
			// 
			// buttonDecrypt_with_CRT
			// 
			this->buttonDecrypt_with_CRT->Location = System::Drawing::Point(167, 351);
			this->buttonDecrypt_with_CRT->Name = L"buttonDecrypt_with_CRT";
			this->buttonDecrypt_with_CRT->Size = System::Drawing::Size(109, 64);
			this->buttonDecrypt_with_CRT->TabIndex = 9;
			this->buttonDecrypt_with_CRT->Text = L"Decrypt with CRT";
			this->buttonDecrypt_with_CRT->UseVisualStyleBackColor = true;
			this->buttonDecrypt_with_CRT->Click += gcnew System::EventHandler(this, &MyForm::buttonDecrypt_with_CRT_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(869, 655);
			this->Controls->Add(this->buttonDecrypt_with_CRT);
			this->Controls->Add(this->label_time_elapsed);
			this->Controls->Add(this->buttEncryption);
			this->Controls->Add(this->buttDecryption);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxUserInput);
			this->Controls->Add(this->comboBoxModeSelc);
			this->Controls->Add(this->RSA);
			this->Controls->Add(this->textBox_input);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MyForm";
			this->Text = L"RSA";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		int mode[] = { 4096,2048,1024,512 };
		int select = this->comboBoxModeSelc->SelectedIndex;
		if (select > 3 || select < 0) select = 3;
		switch (select) {
		case 0: this->label1->Text = "RSA status: 4096 bits";
			break;
		case 1: this->label1->Text = "RSA status: 2048 bits";
			break;
		case 2: this->label1->Text = "RSA status: 1024 bits";
			break;
		case 3: this->label1->Text = "RSA status: 512 bits";
			break;
		}
		clock_t start, stop;
		start = clock();
		if (rsa == NULL)rsa = new RSA_util(mode[select]);
		else rsa->RSA_key_pair_gen(mode[select]);
		stop = clock();
		int ms =(int)(double(stop - start) / CLOCKS_PER_SEC *1000);
		
		String^ s;
		if (ms / (1000 * 60)>0) { s += Convert::ToString(ms / (1000 * 60)) + " min(s) "; ms = ms % (1000 * 60); }
		if (ms / 1000 > 0){s += Convert::ToString(ms / 1000) + " sec(s) "; ms %= 1000;}
		s+= Convert::ToString(ms) + " ms";
		this->label_time_elapsed->Text = "It takes " + s+" to generate the key pair";
		rsa->RSA_CRT_Preprocessing();
		//this->button1->Text = "Finished!";
	}
	private: System::Void RSA_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		this->button1->Text = "Generate";
		this->textBox_input->Text = System::Convert::ToString(this->RSA->SelectedIndex);
		if (rsa != NULL) {
			switch(this->RSA->SelectedIndex) {
			case 0:
			this->textBox_input->Text= marshal_as<System::String^>(rsa->printBIGNUM(rsa->p));
				break;
			case 1:
				this->textBox_input->Text = marshal_as<System::String^>(rsa->printBIGNUM(rsa->q));
				break;
			case 2:
				this->textBox_input->Text = marshal_as<System::String^>(rsa->printBIGNUM(rsa->pq));
				break;
			case 3:
				this->textBox_input->Text = marshal_as<System::String^>(rsa->printBIGNUM(rsa->pbkey));
				break;
			case 4:
				this->textBox_input->Text = marshal_as<System::String^>(rsa->printBIGNUM(rsa->pvkey));
			}
		}
		else this->textBox_input->Text = "Create the rsa first!";
	}
private: System::Void buttEncryption_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ msg=this->textBoxUserInput->Text->ToString();
	if (rsa==NULL||rsa->mode < 0||String::IsNullOrEmpty(msg)) this->textBox_input->Text = "Create the rsa first!";
	else {
		char* result = NULL;
		std::string m=marshal_as<std::string>(msg);
			result=rsa->RSA_encryption(m.c_str(), rsa->pbkey, rsa->pq);
		this->textBox_input->Text = marshal_as<String^>(result);
	}
}
private: System::Void buttDecryption_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ msg = this->textBoxUserInput->Text->ToString();
	if (rsa == NULL || rsa->mode < 0 || String::IsNullOrEmpty(msg)) this->textBox_input->Text = "Create the rsa first!";
	else {
		char* result = NULL;
		std::string m = marshal_as<std::string>(msg);
			result= rsa->RSA_decryption(m.c_str(), rsa->pvkey, rsa->pq);
		this->textBox_input->Text = marshal_as<String^>(result);
	}
}

private: System::Void buttonDecrypt_with_CRT_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ msg = this->textBoxUserInput->Text->ToString();
	if (rsa == NULL || rsa->mode < 0 || String::IsNullOrEmpty(msg)) this->textBox_input->Text = "Create the rsa first!";
	else {
		char* result = NULL;
		std::string m = marshal_as<std::string>(msg);
		result = rsa->RSA_decryption_with_CRT(m.c_str());
		this->textBox_input->Text = marshal_as<String^>(result);
	}
}
};
}
