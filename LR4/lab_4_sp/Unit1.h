//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//#include <String>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TEdit *Edit1;
	TButton *Butt3;
	TButton *Button4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Butt3Click(TObject *Sender);
	//void __fastcall FormClick(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);

	//void __fastcall FormActivate(TObject *Sender);
	//void __fastcall FormShow(TObject *Sender);
	//void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	void DrawPic();
	void DrawBott();
	void PrintFonts();
	void DrawEllipse();
    void DrawClient();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
