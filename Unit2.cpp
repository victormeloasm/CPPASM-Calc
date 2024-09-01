#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop
#include "Unit2.h"
#include <System.SysUtils.hpp>

#include <emmintrin.h>

#include <smmintrin.h>


#include <cmath>


#define e_euler 2.718281828459045235
#define ln2 0.693147180559945309417236294

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm2 * Form2;

using namespace std;

__fastcall TForm2::TForm2(TComponent * Owner): TForm(Owner) {}

int64_t vrand() {
    int64_t randomValue;
    unsigned char success;

    __asm {
        rdrand rax
        mov randomValue, rax
        setc success
    }

    if (success) {
        return randomValue & 0x7FFFFFFFFFFFFFFF;
    } else {
        return 0;
    }
}

double vadd(double a, double b) {
    double result;
    __asm {
        movsd xmm0, a
        movsd xmm1, b
        addsd xmm0, xmm1
        movsd result, xmm0
    }
    return result;
}

double vsub(double a, double b) {
    double result;
    __asm {
        movsd xmm0, a
        movsd xmm1, b
        subsd xmm0, xmm1
        movsd result, xmm0
    }
    return result;
}

double vmul(double a, double b) {
    double result;
    __asm {
        movsd xmm0, a
        movsd xmm1, b
        mulsd xmm0, xmm1
        movsd result, xmm0
    }
    return result;
}

double vdiv(double a, double b) {
	double result;
	if (b<=0) {
    return 0;
	}
    __asm {
		movsd xmm0, a
		movsd xmm1, b
		xorps xmm2, xmm2
		comisd xmm1, xmm2
		jz     divide_by_zero
		divsd xmm0, xmm1
		jmp    done

    divide_by_zero:
		movsd xmm0, [nan]

    done:
		movsd result, xmm0
	}
    return result;
}
int64_t factorial(int n) {
    int64_t result = 1;
    if (n < 0) return 0;

    asm {
        mov     rax, 1
        mov     rcx, n
        test    rcx, rcx
        jz      end_factorial

    factorial_loop:
        mul     rcx
        dec     rcx
        jnz     factorial_loop

        mov     result, rax

    end_factorial:
    }
    return result;
}


double vabs(double value) {
   double result;
   static
   const __int64 mask = 0x7FFFFFFFFFFFFFFF;
   __asm {
      movsd xmm0, value
      andpd xmm0, [mask]
      movsd result, xmm0
   }
   return result;
}

double vpi() {
   double result = 0.0;
   asm {
      finit
      wait
      fldpi
      fstp result
   }
   return result;
}

double ToRad(double value) {
   double result = 0.0;
   int rad = 180;
   __asm {
      finit
      wait
      fild rad
      fldpi
      fdiv st(0), st(1)
      fld value
      fmul st(0), st(1)
      fstp result
   }
   return result;
}

double vsin(double angle) {
   double result = 0.0;
   asm {
      finit
      fld angle
      fsin
      fstp result
   }
   return result;
}

double vcos(double angle) {
   double result;
   asm {
      finit
      fld angle
      fcos
      fstp result
   }
   return result;
}

double vln(double value) {
   const double ln2_val = 0.693147180559945309417236294;

   if (value <= 0.0) {
      return std::numeric_limits < double > ::quiet_NaN(); // Retorna NaN para valores inválidos
   }

   double result = 0.0;
   double temp = (value - 1.0) / (value + 1.0);
   double temp_squared = temp * temp;
   double term = temp;
   int n = 1;

   while (vabs(term) > 1e-15) {
      result += term / n;
      term *= temp_squared;
      n += 2;
   }

   result *= 2.0;

   return result;
}

double vsqrt(double value) {
   double result;
   asm {
      movsd xmm0, value
      sqrtsd xmm0, xmm0
      movsd result, xmm0
   }
   return result;
}

double invSqrt(double value) {
   double result = 0.0;
   double one = 1.0;
   asm {
      movsd xmm0, value
      sqrtsd xmm0, xmm0
      movsd xmm1, one
      divsd xmm1, xmm0
      movsd result, xmm1
   }
   return result;
}

double vtan(double angle) {
   return vsin(ToRad(angle)) / vcos(ToRad(angle));
}

double vcot(double angle) {
   return vcos(ToRad(angle)) / vsin(ToRad(angle));
}

double varctan(double value) {
   double result;
   asm {
      finit
      fld value
      fld1
      fpatan
      fstp result
   }
   return result;
}

double vlog2(double value) {
   double result = 0.0;
   asm {
      fld1
      fld value
      fyl2x
      fstp result
   }
   return result;
}


double vasin(double x) {
   if (x < -1.0 || x > 1.0) {
      return std::numeric_limits < double > ::quiet_NaN();
   }

   const double pi = 3.14159265358979323846;

   double result;
   if (std::abs(x) <= 0.5) {
      result = x + x * x * x * (0.166666666666666657 + x * x * (0.03333333333333333 + x * x * 0.002777777777777778));
   } else {
      double y = vsqrt(1.0 - x * x);
      if (x > 0) {
         result = (pi / 2.0) - varctan(y / x);
      } else {
         result = -(pi / 2.0) - varctan(y / x);
      }
   }

   return result;
}

double vlne2() {
   double result = 0.0;
   __asm {
      finit
      wait
      fldln2
      fstp result
   }
   return result;
}

double vlogten2() {
   double result = 0.0;
   __asm {
      finit
      wait
      fldlg2
      fstp result
   }
   return result;
}

double vlog2e() {
   double result = 0.0;
   __asm {
      finit
      wait
      fldl2e
      fstp result
   }
   return result;
}

double vlogtwo10() {
   double result = 0.0;
   __asm {
      finit
      wait
      fldl2t
      fstp result
   }
   return result;
}

double vpow(double base, int exp) {
double result = 0.0;
__asm {
       fild exp
       fld base

       fyl2x
       fld st(0)
       frndint
       fsub st(1), st(0)
       fxch st(1)
       f2xm1
       fld1
       fadd
       fscale
       fstp result
    }
    return result;
}
void __fastcall TForm2::Button1Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double raiz = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(vsqrt(raiz));
   }
}

void __fastcall TForm2::Button2Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double angle = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(vsin(ToRad(angle)));
   }
}

void __fastcall TForm2::Button3Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double angle = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(vcos(ToRad(angle)));
   }
}

void __fastcall TForm2::Button4Click(TObject * Sender) {
   Edit1 -> Text = EmptyStr;
}

void __fastcall TForm2::Button5Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      try {
         double value = StrToFloat(Edit1 -> Text);
         Edit1 -> Text = FloatToStr(invSqrt(value));
      } catch (...) {
         MessageBoxA(NULL, "O valor inserido não é um número válido.", "Erro", MB_OK | MB_ICONERROR);
      }
   }
}

void __fastcall TForm2::Button6Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double value = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(vtan(value));
   }
}

void __fastcall TForm2::Button7Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double value = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(vcot(value));
   }
}

void __fastcall TForm2::Button8Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double angle = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(varctan(ToRad(angle)));
   }
}

void __fastcall TForm2::Button9Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double result;
      double angle = StrToFloat(Edit1 -> Text);
      result = ToRad(angle);
      double arcResult = vasin(result);

      // Use FormatFloat to ensure 15 digits of precision
      Edit1 -> Text = FormatFloat("0.000000000000000", arcResult);
   }
}

void __fastcall TForm2::Button10Click(TObject * Sender) {
   Edit1 -> Text = FloatToStr(e_euler);
}

void __fastcall TForm2::Button11Click(TObject * Sender) {
   Edit1 -> Text = FloatToStr(vpi());
}

void __fastcall TForm2::Button12Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double log = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr(vlog2(log));
   }
}

void __fastcall TForm2::Button13Click(TObject *Sender) {
	if (Edit1->Text.IsEmpty() || Edit2->Text.IsEmpty()) {
        MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
    } else {
        try {
            double base = StrToFloat(Edit1->Text);
            int exp = StrToInt(Edit2->Text);
            double result = vpow(base, exp);
            Edit1->Text = FloatToStr(result);
        } catch (...) {
            MessageBoxA(NULL, "Erro na conversão dos valores.", "Aviso", MB_OK | MB_ICONWARNING);
        }
    }
}

void __fastcall TForm2::Button14Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
      MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
	  double ln = StrToFloat(Edit1 -> Text);
	  Edit1 -> Text = FloatToStr(vln(ln));
   }
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Button16Click(TObject * Sender) {

   Edit1 -> Text = FloatToStr(vlne2());

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button17Click(TObject * Sender) {
   Edit1 -> Text = FloatToStr(vlogten2());
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button18Click(TObject * Sender) {
   Edit1 -> Text = FloatToStr(vlog2e());
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button15Click(TObject * Sender) {
   if (Edit1 -> Text.IsEmpty()) {
	  MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
      double texto = 0.0;
      texto = StrToFloat(Edit1 -> Text);
      Edit1 -> Text = FloatToStr((vabs(texto)));
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button19Click(TObject * Sender) {
   Edit1 -> Text = FloatToStr(vlogtwo10());
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button20Click(TObject *Sender)
{
 if (Edit1 -> Text.IsEmpty()) {
	  MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
   int64_t fact = floor(StrToFloat(Edit1 -> Text));
	  Edit1 -> Text = IntToStr(factorial(fact));
   }


}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
    if (!((Key >= '0' && Key <= '9') || Key == ',' || Key == '\b')) {
        Key = 0;
    }

    if (Key == ',' && Edit1->Text.Pos(",") > 0) {
        Key = 0;
    }
}


void __fastcall TForm2::Button21Click(TObject *Sender)
{
   Clipboard()->AsText = Edit1->Text;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm2::Button22Click(TObject *Sender) {
    double secondNumber = StrToFloat(Edit1->Text);
    double result;

    if (firstInputDone) {
        if (operation == '+') {
            result = vadd(firstNumber, secondNumber);
        } else if (operation == '-') {
            result = vsub(firstNumber, secondNumber);
        } else if (operation == '*') {
            result = vmul(firstNumber, secondNumber);
        } else if (operation == '/') {
            result = vdiv(firstNumber, secondNumber);
        }
        Edit1->Text = FloatToStr(result);
        firstInputDone = false;
    } else {
        firstNumber = secondNumber;
        operation = '+';
        Edit1->Text = "";
        firstInputDone = true;
    }

    Edit1->SetFocus(); // Volta o foco para o Edit1
}

void __fastcall TForm2::Button24Click(TObject *Sender) {
    double secondNumber = StrToFloat(Edit1->Text);
    double result;

    if (firstInputDone) {
        if (operation == '+') {
            result = vadd(firstNumber, secondNumber);
        } else if (operation == '-') {
            result = vsub(firstNumber, secondNumber);
        } else if (operation == '*') {
            result = vmul(firstNumber, secondNumber);
        } else if (operation == '/') {
            result = vdiv(firstNumber, secondNumber);
        }
        Edit1->Text = FloatToStr(result);
        firstInputDone = false;
    } else {
        firstNumber = secondNumber;
        operation = '*';
        Edit1->Text = "";
        firstInputDone = true;
    }

    Edit1->SetFocus(); // Volta o foco para o Edit1
}

void __fastcall TForm2::Button25Click(TObject *Sender) {
	double secondNumber = StrToFloat(Edit1->Text);
    double result;

    if (firstInputDone) {
        if (operation == '+') {
            result = vadd(firstNumber, secondNumber);
        } else if (operation == '-') {
            result = vsub(firstNumber, secondNumber);
        } else if (operation == '*') {
            result = vmul(firstNumber, secondNumber);
        } else if (operation == '/') {
            result = vdiv(firstNumber, secondNumber);
        }
        Edit1->Text = FloatToStr(result);
        firstInputDone = false;
    } else {
        firstNumber = secondNumber;
        operation = '-';
        Edit1->Text = "";
        firstInputDone = true;
	}

    Edit1->SetFocus(); // Volta o foco para o Edit1
}

void __fastcall TForm2::Button23Click(TObject *Sender) {
    double secondNumber = StrToFloat(Edit1->Text);
    double result;

    if (firstInputDone) {
        if (operation == '+') {
            result = vadd(firstNumber, secondNumber);
        } else if (operation == '-') {
            result = vsub(firstNumber, secondNumber);
        } else if (operation == '*') {
            result = vmul(firstNumber, secondNumber);
        } else if (operation == '/') {
            result = vdiv(firstNumber, secondNumber);
        }
        Edit1->Text = FloatToStr(result);
        firstInputDone = false;
    } else {
        firstNumber = secondNumber;
        operation = '/';
        Edit1->Text = "";
        firstInputDone = true;
    }

	Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button26Click(TObject *Sender)
{
if (Edit3 -> Text.IsEmpty()) {
	  MessageBoxA(NULL, "O campo não pode ficar vazio.", "Aviso", MB_OK | MB_ICONWARNING);
   } else {
    int64_t maxRange = StrToInt(Edit3->Text);
    int64_t randomValue = vrand() % (maxRange + 1);
    Edit1->Text = IntToStr(randomValue);
}
//---------------------------------------------------------------------------
 }
