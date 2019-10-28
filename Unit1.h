//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ExtCtrls.hpp>
 #include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
#include <NMUDP.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TStatusBar *StatusBar;
    TCoolBar *CoolBar1;
    TComboBox *cbURL;
    TToolBar *ToolBar1;
    TToolButton *tbBack;
    TToolButton *tbForward;
    TToolButton *ToolButton6;
    TToolButton *tbStop;
    TToolButton *tbRefresh;
    TToolButton *tbHome;
    TToolButton *ToolButton14;
    TToolButton *tbSearch;
    TToolButton *ToolButton15;
    TToolButton *tbPrint;
    TToolButton *ToolButton16;
    TCppWebBrowser *WebBrowser;
    TImageList *DisableImageList;
    TImageList *HotImageList;
    TImageList *ImageList;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *File2;
        TMenuItem *Flie1;
        TMenuItem *Filesave1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *File3;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TSavePictureDialog *SavePictureDialog1;
        TFontDialog *FontDialog1;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TColorDialog *ColorDialog1;
        TFindDialog *FindDialog1;
        TButton *Button1;
        TListBox *ListBox1;
        TServerSocket *ServerSocket3;
        TLabel *Label1;
        TLabel *lb_size;
        TLabel *Label3;
        TLabel *lb_receive;
        TLabel *Label2;
        TLabel *Label4;
        TLabel *lb_fast;
        TLabel *lb_filename;
        TProgressBar *bar;
        TButton *Btn_Connect;
        TClientSocket *socket_client;
    void __fastcall tbPrintClick(TObject *Sender);
    void __fastcall tbSearchClick(TObject *Sender);
    void __fastcall tbHomeClick(TObject *Sender);
    void __fastcall tbRefreshClick(TObject *Sender);
    void __fastcall tbStopClick(TObject *Sender);
    void __fastcall tbForwardClick(TObject *Sender);
    void __fastcall tbBackClick(TObject *Sender);
    void __fastcall cbURLKeyPress(TObject *Sender, char &Key);
        void __fastcall File2Click(TObject *Sender);
        void __fastcall Filesave1Click(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall ServerSocket3ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocket3ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServerSocket3ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ServerSocket3ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Btn_ConnectClick(TObject *Sender);
        void __fastcall socket_clientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall socket_clientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        AnsiString str_buf;
        int buffersize;
        int totalsize;
        int receivesize;
        int milesecond;
        AnsiString str_filename;
        AnsiString str_savefilename;
        TFileStream* fs;
       TList* clientlist;
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
