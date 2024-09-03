//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TEdit *Edit1;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TLabel *Label1;
    TButton *Button5;
    TButton *Button6;
    TButton *Button7;
    TButton *Button8;
    TButton *Button9;
    TLabel *Label2;
    TButton *Button10;
    TButton *Button11;
    TButton *Button12;
    TButton *Button13;
    TLabel *Label3;
    TEdit *Edit2;
    TButton *Button14;
    TButton *Button15;
    TButton *Button16;
    TButton *Button17;
    TButton *Button18;
    TButton *Button19;
    TButton *Button20;
    TImage *Image1;
    TButton *Button21;
    TLabel *Label4;
    TButton *Button22;
    TButton *Button23;
    TButton *Button24;
    TButton *Button25;
	TButton *Button26;
	TEdit *Edit3;
	TBevel *Bevel1;
	TButton *Button27;
	TButton *Button28;
	TButton *Button29;
	TButton *Button30;
	TButton *Button31;
	TButton *Button32;
	TButton *Button33;
	TButton *Button34;
	TButton *Button35;
	TButton *Button36;
	TButton *Button37;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button8Click(TObject *Sender);
    void __fastcall Button9Click(TObject *Sender);
    void __fastcall Button10Click(TObject *Sender);
    void __fastcall Button11Click(TObject *Sender);
    void __fastcall Button12Click(TObject *Sender);
    void __fastcall Button13Click(TObject *Sender);
    void __fastcall Button14Click(TObject *Sender);
    void __fastcall Button16Click(TObject *Sender);
    void __fastcall Button17Click(TObject *Sender);
    void __fastcall Button18Click(TObject *Sender);
    void __fastcall Button15Click(TObject *Sender);
    void __fastcall Button19Click(TObject *Sender);
    void __fastcall Button20Click(TObject *Sender);
    void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall Button21Click(TObject *Sender);
    void __fastcall Button22Click(TObject *Sender);
    void __fastcall Button24Click(TObject *Sender);
    void __fastcall Button25Click(TObject *Sender);
    void __fastcall Button23Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall Button32Click(TObject *Sender);
	void __fastcall Button35Click(TObject *Sender);
	void __fastcall Button33Click(TObject *Sender);
	void __fastcall Button34Click(TObject *Sender);
	void __fastcall Button36Click(TObject *Sender);
	void __fastcall Button37Click(TObject *Sender);

private:	// User declarations
    bool firstInputDone;
    double firstNumber;
    char operation;

public:		// User declarations
    __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
