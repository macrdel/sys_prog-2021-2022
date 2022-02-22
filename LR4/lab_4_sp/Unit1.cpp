//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool pic = false;     // для зонтика
bool fonts = false;   // для текста
bool el = false;
bool client = false;
bool move_el = false;
TRect el_rect;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TForm1::DrawPic()
{
	Form1->Canvas->Brush->Color = TColor(0x00FFDF);
	Form1->Canvas->FillRect(TRect(0, 0, 500, 500));
	Form1->Canvas->Pen->Color = clBlue;
	Form1->Canvas->Pen->Width = 12;
	Form1->Canvas->Arc(180, 380, 250, 450, 180, 415, 250, 415);
	Form1->Canvas->MoveTo(250, 415);
	Form1->Canvas->LineTo(250, 225);
	Form1->Canvas->Pen->Color = clBlack;
	Form1->Canvas->Pen->Width = 10;
	Form1->Canvas->Arc(30, 100, 470, 400, 470, 250, 30, 250);
	Form1->Canvas->Arc(30, 225, 140, 275, 140, 250, 30, 250);
	Form1->Canvas->Arc(140, 225, 360, 275, 360, 250, 140, 250);
	Form1->Canvas->Arc(360, 225, 470, 275, 470, 250, 360, 250);
	Form1->Canvas->Pen->Width = 8;
	Form1->Canvas->MoveTo(250, 100);
	Form1->Canvas->LineTo(250, 80);
	Form1->Canvas->Arc(140, 100, 360, 450, 360, 250, 140, 250);
	Form1->Canvas->Brush->Color = TColor(0x66CDAA);
	Form1->Canvas->FloodFill(105, 200, TColor(0x00FFDF), fsSurface);
	Form1->Canvas->Brush->Color = TColor(0x6A5ACD);
	Form1->Canvas->FloodFill(250, 140, TColor(0x00FFDF), fsSurface);
	Form1->Canvas->Brush->Color = TColor(0xA0522D);
	Form1->Canvas->FloodFill(375, 180, TColor(0x00FFDF), fsSurface);
}

void TForm1::DrawBott()
{
	 Form1->Canvas->Pen->Color = (TColor)RGB(0, 120, 215);
	 Form1->Canvas->Pen->Width = 5;
	 Form1->Canvas->Rectangle(240, 575, 410, 610);
	 Form1->Canvas->Brush->Color = TColor(0xE2E2E2);
	 TRect rect = TRect(240, 575, 410, 610);
	 Form1->Canvas->FillRect(rect);
	 Form1->Canvas->Font->Name = "Tahoma";
	 Form1->Canvas->Font->Size = 9;
	 Form1->Canvas->Font->Color = clBlack;
	 Form1->Canvas->TextRect(rect, 300, 584, "Button2");
}

void TForm1::PrintFonts()
{
	 TRect rects[3];
	 rects[0] = TRect(510, 0, 990, 150);
	 rects[1] = TRect(510, 150, 940, 300);
	 rects[2] = TRect(510, 300, 880, 450);
	 Form1->Canvas->Brush->Color = clBlue;
	 Form1->Canvas->FillRect(rects[0]);
	 Form1->Canvas->Font->Name = "Times New Roman";
	 Form1->Canvas->Font->Size = 35;
	 Form1->Canvas->Font->Color = clBlack;
	 Form1->Canvas->TextRect(rects[0], 515, 10, "На улице дождь!");
	 Form1->Canvas->Brush->Color = clYellow;
	 Form1->Canvas->FillRect(rects[1]);
	 Form1->Canvas->Font->Name = "MS Sans Serif";
	 Form1->Canvas->Font->Size = 25;
	 Form1->Canvas->Font->Color = clBlue;
	 Form1->Canvas->TextRect(rects[1], 515, 160, "Побереги себя!");
	 Form1->Canvas->Brush->Color = clRed;
	 Form1->Canvas->FillRect(rects[2]);
	 Form1->Canvas->Font->Name = "Arial";
	 Form1->Canvas->Font->Size = 20;
	 Form1->Canvas->Font->Color = clGreen;
	 Form1->Canvas->TextRect(rects[2], 515, 310, "Не забудь зонтик!");
}

void TForm1::DrawEllipse(){
	Form1->Canvas->Brush->Color = (TColor)RGB(100, 200, 250);
	Form1->Canvas->Pen->Color = (TColor)RGB(13, 14, 156);
	Form1->Canvas->Pen->Width = 2;
	TRect rect = el_rect;
	Form1->Canvas->Ellipse(rect);
	Form1->Canvas->FloodFill(el_rect.left + 150, el_rect.top + 150, clGray, fsSurface);}

void TForm1::DrawClient() {
	TRect rect;
	::GetWindowRect(Form1->Handle, &rect);
	Form1->Canvas->Brush->Color = (TColor)RGB(Random(255), Random(255), Random(255));
	Canvas->FillRect(rect);
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	DrawPic();
	pic = true; // включаем
}

void __fastcall TForm1::Butt3Click(TObject *Sender)
{
	el_rect = TRect(0, 0, 300, 300);
	DrawEllipse();
	el = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Edit1->Text = "x - " + IntToStr(X) + " y - " + IntToStr(Y);

	if (X <= 410 && X >= 240 && Y <= 610 && Y >= 575) {
		 TRect rect = TRect(240, 575, 410, 610);
		::InvalidateRect(Form1->Handle, &rect, true);
		Form1->Canvas->Pen->Color = (TColor)RGB(0, 120, 215);
		Form1->Canvas->Pen->Width = 2;
		Form1->Canvas->Rectangle(240, 575, 410, 610);
		Form1->Canvas->Brush->Color = (TColor)RGB(230, 240, 250);
		Form1->Canvas->FillRect(rect);
		::Sleep(100);
		::InvalidateRect(Form1->Handle, &rect, true);
		DrawBott();
		PrintFonts();
		fonts = true; // включаем
	}
	if (X <= 300 && Y <= 300 && (((X - 150) * (X - 150) +  (Y - 150) * (Y - 150)) <= 150 * 150))
	{
		if (Button == mbRight) {
			el = false;
			::InvalidateRect(Form1->Handle, &el_rect, true);
		}
		else if (Button == mbLeft)
			move_el = true;

	}
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
	DrawBott();
	if (pic) DrawPic();
	if (fonts) PrintFonts();
	if (el) DrawEllipse();
	if (client) DrawClient();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
	if (pic) DrawPic();
	if (el) DrawEllipse();
	if (client) DrawClient();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	DrawClient();
	client = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if (move_el) move_el = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if (move_el && X >= el_rect.left && Y >= el_rect.top && X <= el_rect.right && Y <= el_rect.bottom &&
	   (((X - 150 - el_rect.left) * (X - 150 - el_rect.left) +
	   (Y - 150 - el_rect.top) * (Y - 150 - el_rect.top)) <= 150 * 150))
	{
		::InvalidateRect(Form1->Handle, &el_rect, true);
		el_rect.top += 1;
		el_rect.bottom += 1;
		el_rect.right += 1;
		el_rect.left += 1;
		::InvalidateRect(Form1->Handle, &el_rect, true);
	}
}
//---------------------------------------------------------------------------

