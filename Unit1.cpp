//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
int ClientCount;
int i =0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
        fs = NULL;
    str_filename = "";
    str_savefilename = "";
    totalsize = 0;
    receivesize = 0;
    buffersize =0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbPrintClick(TObject *Sender)
{
// 인쇄하기
    WebBrowser->ExecWB(Shdocvw_tlb::OLECMDID_PRINT, Shdocvw_tlb::OLECMDEXECOPT_DODEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tbSearchClick(TObject *Sender)
{
   WebBrowser->GoSearch();  // 검색하기

}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbHomeClick(TObject *Sender)
{
    WebBrowser->GoHome();    // 홈으로

}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbRefreshClick(TObject *Sender)
{
    WebBrowser->Refresh();   // 새로고침

}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbStopClick(TObject *Sender)
{
   WebBrowser->Stop();      // 정지

}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbForwardClick(TObject *Sender)
{
    WebBrowser->GoForward(); // 앞 페이지로 가기

}
//---------------------------------------------------------------------------
void __fastcall TForm1::tbBackClick(TObject *Sender)
{
    WebBrowser->GoBack();    // 전 페이지로 가기

}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbURLKeyPress(TObject *Sender, char &Key)
{
  if (Key == 0xd)                    // 인터넷 사이트가 유해 사이트인지 서버에게 요청
   /* {
        int CT=0;
	    AnsiString ReceiveText=cbURL->Text;
        Form1->InternetSite->Fields[0]->DataSet->First();
        for (int i=0;i<Form1->InternetSite->Fields[0]->DataSet->RecordCount;i++)
        {
            if (ReceiveText.Pos(Form1->InternetSite->Fields[0]->Text))
            {
                CT++;
            }
            Form1->InternetSite->Fields[0]->DataSet->Next();
        }
     */
        //if (CT == 0)
        {
        AnsiString ReceiveText=cbURL->Text;
        	AnsiString URL = ReceiveText;
        	WebBrowser->Navigate(WideString(URL).c_bstr(), EmptyParam, EmptyParam, EmptyParam, EmptyParam);
        	cbURL->Items->Add(ReceiveText);
        }
	    /*else
	    {
	    	ShowMessage("유해사이트는 접속하실수 없습니다.");
	    }
    }*/
}
//---------------------------------------------------------------------------
/*void __fastcall TForm1::WebBrowserCommandStateChange(TObject *Sender,
      long Command, VARIANT_BOOL Enable)
{
    switch (Command)                // 전 페이지, 앞 페이지 로딩
    {
        case CSC_NAVIGATEBACK: tbBack->Enabled = Enable; break;
        case CSC_NAVIGATEFORWARD: tbForward->Enabled = Enable; break;
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::WebBrowserDocumentComplete(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL)
{
    // 등록한 홈페이지 로딩
    cbURL->Text = WebBrowser->LocationURL;
}
*/
void __fastcall TForm1::File2Click(TObject *Sender)
{
        OpenDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Filesave1Click(TObject *Sender)
{
        SaveDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
        SavePictureDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        FontDialog1->Execute();
        ColorDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
        FindDialog1->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ServerSocket3ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        clientlist->Add(Socket);
    ListBox1->Items->AddObject(Socket->RemoteAddress, Socket);
       // ListBox1->Items->Add(Socket->RemoteAddress);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket3ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        int idx = ListBox1->Items->IndexOfObject(Socket);

    if(idx == -1) return;
    ListBox1->Items->Delete(idx);
    clientlist->Remove(Socket);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket3ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    int idx = ListBox1->Items->IndexOfObject(Socket);

    if(idx == -1) return;
    ListBox1->Items->Delete(idx);
    clientlist->Remove(Socket);
    Socket->Close();

    ErrorCode = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket3ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AnsiString str_data="";

    AnsiString cls_str="";
    cls_str = Socket->ReceiveText();

    //파일 전송이 다 끝나면 완료한다.
    int idx = cls_str.Pos("#FILEDOWNLOADED#");
    if(idx <= 0) return;

    cls_str.Delete(idx, 16);
    idx = cls_str.Pos("#");
    AnsiString str_filename = cls_str.SubString(1, idx-1);
    cls_str.Delete(1, idx);
    idx = cls_str.Pos("#");
    AnsiString str_downloadedsize = cls_str.SubString(1, idx-1);
    int downloadedsize = StrToInt(str_downloadedsize);

    TFileStream* fs = new TFileStream(str_filename, fmOpenRead|fmShareCompat);
    int totalsize = fs->Size;
    fs->Position = downloadedsize;

    if((totalsize-downloadedsize) > (1024))
    {
        str_data.SetLength(1024);
        fs->Read(str_data.c_str(), 1024);
    }
    else
    {
        str_data.SetLength(totalsize-downloadedsize);
        fs->Read(str_data.c_str(), totalsize-downloadedsize);
    }
    delete fs;

    AnsiString str= "#FILEDOWNLOADING#"+ IntToStr(str_data.Length()) + "#";
    str = str + str_data;
    Socket->SendText(str);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        int idx = ListBox1->ItemIndex;
    if(idx == -1) return;

    TCustomWinSocket* Socket;
    Socket = (TCustomWinSocket*)clientlist->Items[idx];

    TOpenDialog* dlg = new TOpenDialog(this);
    TFileStream* fs;
    AnsiString fstr;
    dlg->InitialDir = "c:\\";
    dlg->DefaultExt = "*.*";
    if(dlg->Execute() == TRUE)
    {
        AnsiString fstr;
        fs = new TFileStream(dlg->FileName, fmOpenRead|fmShareCompat);
        AnsiString str = "#FILEDOWNSTART#" + IntToStr(fs->Size)+"#"+ dlg->FileName + "#";
        Socket->SendText(str);
        delete fs;
    }
    delete dlg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
         clientlist = new TList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        delete clientlist;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Btn_ConnectClick(TObject *Sender)
{
        socket_client->Active = true;
    socket_client->Open();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::socket_clientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        AnsiString str = Socket->ReceiveText();

    int idx = str.Pos("#FILEDOWNSTART#");

    if(idx>0)
    {
        lb_size->Caption = "0 KByte";
        lb_receive->Caption = "0 KByte";

        if(str_filename != "") return;

        str.Delete(idx, 15);
        idx = str.Pos("#");
        AnsiString str_count = str.SubString(1, idx-1);
        totalsize = StrToInt(str_count);

        str.Delete(1, idx);
        idx = str.Pos("#");
        str_filename = str.SubString(1, idx-1);

        if(MessageDlg("현재 받을 파일은 바이러스일수도 있습니다.\n\n파일을 전송받으시겠습니까?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
        {
            TSaveDialog* dlg = new TSaveDialog(this);
            dlg->InitialDir = "";
            dlg->FileName = ExtractFileName(str_filename);
            dlg->DefaultExt = ExtractFileExt(str_filename);

            if(dlg->Execute() == TRUE)
            {
                str_savefilename = dlg->FileName;
                AnsiString str_require = "#FILEDOWNLOADED#" + str_filename + "#0#";

                Socket->SendText(str_require);
                receivesize = 0;

                fs = new TFileStream(str_savefilename, fmCreate|fmShareCompat);

                lb_filename->Caption = ExtractFileName(str_filename);
                int byte_totalsize = totalsize/1024;
                lb_size->Caption = IntToStr(byte_totalsize) + " KByte";
                lb_receive->Caption = "0 KByte";
                bar->Max = totalsize;
                bar->Min = 0;
                bar->Position = 0;
                milesecond = GetTickCount();
                lb_fast->Caption = "0 Kbyte/sec";
            }
            else
            {
                fs = NULL;
                str_buf = "";
                str_filename = "";
                str_savefilename = "";
                totalsize = 0;
                receivesize = 0;
                buffersize =0;

                lb_filename->Caption = "";
                lb_receive->Caption = "0 KByte";
                lb_size->Caption = "0 KByte";
                bar->Position = 0;
                lb_fast->Caption = "0 Kbyte/sec";

            }
        }
        else
        {
                fs = NULL;
                str_buf = "";
                str_filename = "";
                str_savefilename = "";
                totalsize = 0;
                receivesize = 0;
                buffersize =0;

                lb_filename->Caption = "";
                lb_receive->Caption = "0 KByte";
                lb_size->Caption = "0 KByte";
                bar->Position = 0;
                lb_fast->Caption = "0 Kbyte/sec";
         }
    }
    else
    {
        idx = str.Pos("#FILEDOWNLOADING#");
        if(idx >0)
        {
            str.Delete(idx, 17);
            idx = str.Pos("#");

            AnsiString str_buffersize = str.SubString(1, idx-1);
            buffersize = StrToInt(str_buffersize);

            str.Delete(1, idx);
            str_buf = "";

            str_buf = str;

            receivesize = receivesize + str.Length();
            int byte_receivesize = receivesize/1024;
            lb_receive->Caption = IntToStr(byte_receivesize) + " KByte";

            int fast = GetTickCount();
            fast = fast-milesecond;
            fast = (byte_receivesize*1000)/ fast;
            lb_fast->Caption = IntToStr(fast) + " KByte/sec";
            bar->Position = receivesize;

            if(receivesize == totalsize)
            {
                fs->Write(str_buf.c_str(), str_buf.Length());

                delete fs;
                fs = NULL;
                str_buf = "";
                str_filename = "";
                str_savefilename = "";
                totalsize = 0;
                receivesize = 0;
                buffersize =0;

                lb_filename->Caption = "";
                lb_receive->Caption = "0 KByte";
                lb_size->Caption = "0 KByte";
                bar->Position = 0;
                lb_fast->Caption = "0 Kbyte/sec";

                ShowMessage("다운로드 완료");
            }
            else if(str_buf.Length() >= buffersize)
            {
                fs->Write(str_buf.c_str(), str_buf.Length());
                AnsiString str_require = "#FILEDOWNLOADED#" + str_filename + "#" + IntToStr(receivesize)+ "#";
                Socket->SendText(str_require);
            }
        }
        else
        {
            if(fs == NULL) return;
            str_buf = str_buf + str;
            receivesize = receivesize + str.Length();
            int byte_receivesize = receivesize/1024;
            lb_receive->Caption = IntToStr(byte_receivesize) + " KByte";
            int fast = GetTickCount();
            fast = fast-milesecond;
            fast = (byte_receivesize*1000)/ fast;
            lb_fast->Caption = IntToStr(fast) + " KByte/sec";

            bar->Position = receivesize;

            if(receivesize == totalsize)
            {
                fs->Write(str_buf.c_str(), str_buf.Length());
                delete fs;
                str_buf = "";
                fs == NULL;
                str_filename = "";
                str_savefilename = "";
                totalsize = 0;
                receivesize = 0;
                buffersize = 0;

                lb_filename->Caption = "";
                lb_receive->Caption = "0 KByte";
                lb_size->Caption = "0 KByte";
                bar->Position = 0;
                lb_fast->Caption = "0 Kbyte/sec";

                ShowMessage("다운로드 완료");
            }
            else if(str_buf.Length() >= buffersize)
            {
                fs->Write(str_buf.c_str(), str_buf.Length());
                AnsiString str_require = "#FILEDOWNLOADED#" + str_filename + "#" + IntToStr(receivesize) +"#";
                Socket->SendText(str_require);
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::socket_clientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
        ErrorCode = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        socket_client->Active = FALSE;
}
//---------------------------------------------------------------------------