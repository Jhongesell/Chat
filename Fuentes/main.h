// Autor:     Antonio Carrillo Ledesma.
// R.F.C.:    CAAN-691229-TV7
// Dirección: Amsterdam 312 col. Hipódromo Condesa
// Teléfono:  5-74-43-53

// Propiedad intelectual, todos los derechos reservados conforme a la ley, registro en tr mite
// Revisión  1.0-A


#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ScktComp.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TChatForm : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel1;
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TSpeedButton *SpeedButton1;
        TMemo *Memo1;
        TMemo *Memo2;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *FileConnectItem;
        TMenuItem *Disconnect1;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TServerSocket *ServerSocket;
        TClientSocket *ClientSocket;
        TMenuItem *Edicion;
        TMenuItem *Configuracon1;
        TMenuItem *Ayuda1;
        TMenuItem *Chat1;
        TMenuItem *Acercade1;
        TMenuItem *TipodeLetra1;
        TMenuItem *Color1;
        TMenuItem *MenuEdicionCopiar;
        TMenuItem *MenuEdicionPegar;
        TSpeedButton *SpeedButton2;
        TMenuItem *N2;
        TTimer *Contador;
        TPanel *Panel2;
        TStaticText *Text1;
        TStaticText *Text2;
        TMenuItem *N3;
        TMenuItem *AntonioCarrilloLedesma1;
   void __fastcall FileConnectItemClick(TObject *Sender);
   void __fastcall Exit1Click(TObject *Sender);
   void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket);
   void __fastcall ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket);
   void __fastcall ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket);
   void __fastcall ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket);
   void __fastcall ServerSocketAccept(TObject *Sender,
      TCustomWinSocket *Socket);
   void __fastcall ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket);
   void __fastcall Disconnect1Click(TObject *Sender);
   void __fastcall ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode);
   void __fastcall ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall Chat1Click(TObject *Sender);
        void __fastcall Acercade1Click(TObject *Sender);
        void __fastcall MenuEdicionCopiarClick(TObject *Sender);
        void __fastcall MenuEdicionPegarClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall ContadorTimer(TObject *Sender);
        void __fastcall AntonioCarrilloLedesma1Click(TObject *Sender);
private:	// User declarations
        int   Tiempo;
        int   xtiempo;
        int   hh;
        int   mm;
        int   ss;
        char  xcad[200];
        void  __fastcall OnIdle(TObject *Sender, bool &Done);
        // Encripta la cadena
        AnsiString       EncriptaCadena(AnsiString cad);
        // Desencripta la cadena
        AnsiString       DesEncriptaCadena(AnsiString cad);
public:		// User declarations
        bool IsServer;
        String Server;
        int Conectado;
        __fastcall TChatForm(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern TChatForm *ChatForm;
//---------------------------------------------------------------------------
#endif
