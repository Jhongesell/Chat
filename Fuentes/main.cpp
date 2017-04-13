// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#include <vcl.h>
#include <clipbrd.hpp>
#include <mmsystem.h>
#include <stdio.h>
#include "Acecade.h"
#include "Ayuda.h"
#include "ACX-WebBrowser.h"
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma link "ScktComp"
#pragma resource "*.dfm"
TChatForm *ChatForm;
char *TITULO = "Chat Windows / C++ 1.0";
//---------------------------------------------------------------------------

// Constructor de la clase
__fastcall TChatForm::TChatForm(TComponent* Owner)  : TForm(Owner)
{
}

// Al crear la forma
void __fastcall TChatForm::FormCreate(TObject *Sender)
{
   Application->Title = TITULO;
   Conectado = 0;
   // Tiempo maximo de muestra de Hits
   Application->HintHidePause = 10000;
   try {
      // Carga el icono de la aplicación
      Application->Icon->LoadFromFile("CHAT.ICO");
   } catch (...) {};
   Application->OnIdle = OnIdle;
   PlaySound("PUERTA1.WAV",NULL,SND_ASYNC);
}

// Solicitud de salir
void __fastcall TChatForm::Exit1Click(TObject *Sender)
{
  Close();
}

// Al salir del sistema
void __fastcall TChatForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  Disconnect1Click(this);
  PlaySound("PUERTA2.WAV",NULL,SND_ASYNC);
  ServerSocket->Close();
  ClientSocket->Close();
}

// OnIdle
void  __fastcall TChatForm::OnIdle(TObject *Sender, bool &Done)
{
   if (Conectado) {
      Panel2->Visible = true;
      Memo1->ReadOnly = false;
      SpeedButton1->Enabled = false;
      SpeedButton2->Enabled = true;
      FileConnectItem->Enabled = false;
      Disconnect1->Enabled = true;
    } else {
      Panel2->Visible = false;
      Memo1->ReadOnly = true;
      SpeedButton1->Enabled = true;
      SpeedButton2->Enabled = false;
      FileConnectItem->Enabled = true;
      Disconnect1->Enabled = false;
   }
   bool st = Memo1->SelLength > 0;
   // Activa o desactiva la opcion de Copiar
   MenuEdicionCopiar->Enabled = st;
   // Activa o desactiva la opcion de Pegar
   st = Clipboard()->HasFormat(CF_TEXT);
   MenuEdicionPegar->Enabled = st;
}

// Solicitud de conexion
void __fastcall TChatForm::FileConnectItemClick(TObject *Sender)
{
   if (Conectado) {
      PlaySound("ERROR.WAV",NULL,SND_ASYNC);
      MessageBox(NULL,"Conexión ya establecida",TITULO,MB_ICONSTOP);
      return;
   }
   StatusBar1->Panels->Items[0]->Text = "Connect ...";
   if (ClientSocket->Active){ ClientSocket->Active = false;}
   if (InputQuery("Computer connect to", "Address Name:", Server))
   {
      if (Server.Length() > 0) {
         PlaySound("CONECT.WAV",NULL,SND_ASYNC);
         ClientSocket->Host = Server;
         ClientSocket->Active = true;
         Memo1->Lines->Clear();
         Memo2->Lines->Clear();
      }
   }
}

// Al presionar la tecla ENTER envia el texto
void __fastcall TChatForm::Memo1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
   if (Key == VK_RETURN) {
      AnsiString cad1 = Memo1->Lines->Strings[Memo1->Lines->Count - 1];
      AnsiString cad2;
      cad2 = EncriptaCadena(cad1);
      if (IsServer) ServerSocket->Socket->Connections[0]->SendText(cad2);
      else ClientSocket->Socket->SendText(cad2);
   }
}

//
void __fastcall TChatForm::ClientSocketConnect(TObject *Sender, TCustomWinSocket *Socket)
{
   StatusBar1->Panels->Items[0]->Text = "Connect to: " + Socket->RemoteHost;
   Conectado = 1;
   PlaySound("RING.WAV",NULL,SND_ASYNC);
}

//
void __fastcall TChatForm::Disconnect1Click(TObject *Sender)
{
  if (Conectado) {
     ClientSocket->Close();
     MessageBox(NULL,"Close connetion by user",TITULO,MB_ICONINFORMATION);
     Conectado = 0;
     ServerSocket->Active = false;
  }
}

//
void __fastcall TChatForm::ClientSocketRead(TObject *Sender, TCustomWinSocket *Socket)
{
   AnsiString cad1, cad2;
   cad1 = Socket->ReceiveText();
   cad2 = DesEncriptaCadena(cad1);
   Memo2->Lines->Add(cad2);
}

//
void __fastcall TChatForm::ServerSocketClientRead(TObject *Sender, TCustomWinSocket *Socket)
{
   AnsiString cad1, cad2;
   cad1 = Socket->ReceiveText();
   cad2 = DesEncriptaCadena(cad1);
   Memo2->Lines->Add(cad2);
}

// El server acepta la conexión
void __fastcall TChatForm::ServerSocketAccept(TObject *Sender, TCustomWinSocket *Socket)
{
   IsServer = true;
   Conectado = 2;
   StatusBar1->Panels->Items[0]->Text = "Connect to: " + Socket->RemoteAddress;
   PlaySound("RING.WAV",NULL,SND_ASYNC);
}

// Cliente se conecta
void __fastcall TChatForm::ServerSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
   Memo1->Lines->Clear();
   Memo2->Lines->Clear();
}

// Cliente solicita desconexion
void __fastcall TChatForm::ClientSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
   MessageBox(NULL,"Close connetion",TITULO,MB_ICONINFORMATION);
   Conectado = 0;
   ServerSocket->Active = false;
}

// Error en conexión
void __fastcall TChatForm::ClientSocketError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
   char xcad[200];
   PlaySound("ERROR.WAV",NULL,SND_ASYNC);
   ErrorCode = 0;
   if (Conectado) {
       sprintf(xcad,"Error connecting to: %s",Server.c_str());
       MessageBox(NULL,xcad,TITULO,MB_ICONSTOP);
    } else {
       sprintf(xcad,"Connect fail to: %s",Server.c_str());
       MessageBox(NULL,xcad,TITULO,MB_ICONSTOP);
   }
}

// Al desconectarse el server
void __fastcall TChatForm::ServerSocketClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
   ClientSocket->Active = false;
   Conectado = 0;
   MessageBox(NULL,"Close connetion",TITULO,MB_ICONINFORMATION);
}

// Al cambiar el tamaño de la ventana
void __fastcall TChatForm::FormResize(TObject *Sender)
{
   // Controla la altura minima de la ventana
   if (Height < 379) Height = 379;
   // Controla la anchura minima de la ventana
   if (Width < 445) Width = 445;
   // Ajusta el tamaño de los editores para que sean homogeneos
   int lg = (Memo1->Height + Memo2->Height);
   Memo2->Height = (lg /2);
   Memo1->Height = lg - (lg /2);
}


// Ayuda del programa
void __fastcall TChatForm::Chat1Click(TObject *Sender)
{
   TAyudaForm *Ayuda = new TAyudaForm(this);
   if (Ayuda) {
      Ayuda->Abrir_archivo("Help","General.hlp");
      Ayuda->ShowModal();
      delete Ayuda;
   }
}

// pagina personal de Antonio Carrillo Ledesma
void __fastcall TChatForm::AntonioCarrilloLedesma1Click(TObject *Sender)
{
   TFormaWebBrowzer *vent = new TFormaWebBrowzer(this);
   if (vent) {
       vent->Parametros("http://dinamica1.fciencias.unam.mx/dinamicaNoLineal/Integrantes/ACL/Index.html");
       vent->Show();
   }
}


// Acerca de ...
void __fastcall TChatForm::Acercade1Click(TObject *Sender)
{
   TVAcercaDe *Acercade = new TVAcercaDe(this);
   if (Acercade) {
      Acercade->ShowModal();
      delete Acercade;
   }
}

// Copiar
void __fastcall TChatForm::MenuEdicionCopiarClick(TObject *Sender)
{
   Memo1->CopyToClipboard();
}

// Pegar
void __fastcall TChatForm::MenuEdicionPegarClick(TObject *Sender)
{
   Memo1->PasteFromClipboard();
}


// Timer
void __fastcall TChatForm::ContadorTimer(TObject *Sender)
{
   if (Conectado) {
      Tiempo++;
      xtiempo = Tiempo, hh = 0, mm = 0, ss = 0;
      while(xtiempo > 3599) xtiempo -= 3600, hh++;
      while(xtiempo > 59) xtiempo -= 60, mm++;
      ss = xtiempo;
      sprintf(xcad,"%02d:%02d:%02d",hh,mm,ss);
      Text2->Caption = xcad;
    } else {
      Tiempo = 0;
      if(!ServerSocket->Active) {
         ClientSocket->Active = false;
         ServerSocket->Active = true;
         StatusBar1->Panels->Items[0]->Text = "Listening ...";
      }
   }
}

// Encripta la cadena
AnsiString TChatForm::EncriptaCadena(AnsiString cad)
{
   AnsiString xtemp = cad;
   int i = 0, lg = cad.Length()+2;
   char *xcad = new char[lg];
   strcpy(xcad,strrev(cad.c_str()));
   while (xcad[i]) {
      xcad[i] = ~(xcad[i]+(lg%50));
      i++;
   }
   xtemp = xcad;
   delete []xcad;
   return(xtemp);
}

// Desencripta la cadena
AnsiString TChatForm::DesEncriptaCadena(AnsiString cad)
{
   AnsiString xtemp = cad;
   int i = 0, lg = cad.Length()+2;
   char *xcad = new char[lg];
   strcpy(xcad,strrev(cad.c_str()));
   while (xcad[i]) {
      xcad[i] = (~xcad[i])-(lg%50);
      i++;
   }
   xtemp = xcad;
   delete []xcad;
   return(xtemp);
}

/*
Otras caracteristicas:
  Textos en ingles
*/


