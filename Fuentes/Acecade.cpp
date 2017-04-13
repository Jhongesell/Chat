// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en trámite 1999-2000
// Revisión  1.1-A


#include <vcl\vcl.h>
#include "Acecade.h"
#include "ACX-WebBrowser.h"
#pragma hdrstop


//---------------------------------------------------------------------------
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TVAcercaDe::TVAcercaDe(TComponent* Owner) : TForm(Owner)
{
   // Nombre de la aplicación
   Label10->Caption = Application->Title;
   // Fecha de generacion de la versión
   FechaGeneracion->Caption = __DATE__;
}
//---------------------------------------------------------------------------






void __fastcall TVAcercaDe::Label10Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("//dinamica1.fciencias.unam.mx/dinamicaNoLineal/Integrantes/ACL/Chat/chat.html");
       vent->Show();
   }
}
//---------------------------------------------------------------------------

void __fastcall TVAcercaDe::Label16Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://dinamica1.fciencias.unam.mx/dinamicaNoLineal/Integrantes/ACL/Index.html");
       vent->Show();
   }
}
//---------------------------------------------------------------------------

