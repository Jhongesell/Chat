// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#pragma hdrstop
USEFORM("main.cpp", ChatForm);
USERES("chat.res");
USEFORM("Acecade.cpp", VAcercaDe);
USEFORM("..\Libreria\FORMAS\Ayuda.cpp", AyudaForm);
USEFORM("..\Libreria\FORMAS\ACX-WebBrowser.cpp", FormaWebBrowzer);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
          Application->Initialize();
          Application->CreateForm(__classid(TChatForm), &ChatForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
          Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
