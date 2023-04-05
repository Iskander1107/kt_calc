#include <wx/defs.h>
#include <wx/sizer.h>
#include <wx/wx.h>

#include <string>

//  Класс для фоновой картинки и дугого рисования
class BackPanel : public wxPanel {
  //  Изображение для фона
  wxBitmap image;

 public:
  BackPanel(wxFrame* parent, wxString file, wxBitmapType format);
  // Все рисование происходит когда    происходит событие перерисовки
  void paintEvent(wxPaintEvent& evt);
  //  Эта функция собственно все и будет рисовать
  void paintBack();
  //  wxDC - абстрактный класс для рисования. У него есть реальные наследники:
  // wxPaintDC,  wxClientDC и wxMemoryDC
  void setImage(wxDC& dc);
  void OnMouse(wxMouseEvent& event);
};

//  Основное окно
class CalcFrame : public wxFrame {
  wxBoxSizer *sizer, *sizerP;
  BackPanel* drawPane;
  wxPanel* panel;

  wxBitmapButton* bitmap_btns;
  wxTextCtrl* number_scr;
  wxTextCtrl* display;

  wxTimer* tm;  // объект таймер
  wxGridSizer* gs;

  wxImage* btns;

 public:
  CalcFrame(const wxString& title);
  ~CalcFrame();
  void Upd();
  void pressOne(wxCommandEvent& event);
  void pressSec(wxCommandEvent& event);
};
enum Operand { LEFT_OPERAND, RIGHT_OPERAND };
Operand current_operand = LEFT_OPERAND;
enum Operation { ADD, SUB, MUL, DIV };
Operation current_operation = ADD;
std::string left_op = "", right_op = "";
enum {
  BUTTON_0 = 1000,
  BUTTON_1 = 1001,
  BUTTON_2 = 1002,
  BUTTON_3 = 1003,
  BUTTON_4 = 1004,
  BUTTON_5 = 1005,
  BUTTON_6 = 1006,
  BUTTON_7 = 1007,
  BUTTON_8 = 1008,
  BUTTON_9 = 1009,
  BUTTON_10 = 1010,  // add
  BUTTON_11 = 1011,  // sub
  BUTTON_12 = 1012,  // mul
  BUTTON_13 = 1013,  // dib
  BUTTON_14 = 1014,  // x^y
  BUTTON_15 = 1015,  // arrow up
  BUTTON_16 = 1016,  // swap
  BUTTON_17 = 1017,  // shg
  BUTTON_18 = 1018,  // shgL
  BUTTON_19 = 1019,  // shgR
  BUTTON_20 = 1020,  // sign
  BUTTON_21 = 1021,  // vo
  BUTTON_22 = 1022,  // vp
  BUTTON_23 = 1023,  // sp
  BUTTON_24 = 1024,  // p
  BUTTON_25 = 1025,  // pp
  BUTTON_26 = 1026,  // cx
  BUTTON_27 = 1027,  // f
  BUTTON_28 = 1028,  // bp
  BUTTON_29 = 1029,  // pnt
};

BackPanel::BackPanel(wxFrame* parent, wxString file, wxBitmapType format)
    : wxPanel(parent) {
  image.LoadFile(file, format);
  Connect(wxEVT_PAINT, wxPaintEventHandler(BackPanel::paintEvent));
  Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(BackPanel::OnMouse));
}

void BackPanel::paintEvent(wxPaintEvent& evt) {
  wxPaintDC dc(this);
  setImage(dc);
}

void BackPanel::paintBack() {
  wxClientDC dc(this);
  setImage(dc);
}

void BackPanel::setImage(wxDC& dc) { dc.DrawBitmap(image, 0, 0, false); }

void BackPanel::OnMouse(wxMouseEvent& event) {
  wxString answ;
  int x = event.GetX();
  int y = event.GetY();
  answ = answ.Format(wxT("(%d,  %d)"), x, y);
  wxMessageBox(answ);
};

CalcFrame::CalcFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxPoint(50, 50), wxSize(1920, 1080)) {
  wxInitAllImageHandlers();
  sizer = new wxBoxSizer(wxHORIZONTAL);
  drawPane = new BackPanel(this, wxT("calcApp.png"), wxBITMAP_TYPE_PNG);
  panel = new wxPanel(this, wxID_ANY);
  sizer->Add(drawPane, 1, wxEXPAND, 10);

  btns = new wxImage[50];
  bitmap_btns = new wxBitmapButton[50];

  for (size_t i = 0; i < 10; i++) {
    new (btns + i) wxImage(wxT("Calc_pict/k" + std::to_string(i) + ".png"),
                           wxBITMAP_TYPE_PNG);
  }
  btns[10] = wxImage(wxT("Calc_pict/plus.png"), wxBITMAP_TYPE_PNG);
  btns[11] = wxImage(wxT("Calc_pict/minus.png"), wxBITMAP_TYPE_PNG);
  btns[12] = wxImage(wxT("Calc_pict/mult.png"), wxBITMAP_TYPE_PNG);
  btns[13] = wxImage(wxT("Calc_pict/delen.png"), wxBITMAP_TYPE_PNG);
  btns[14] = wxImage(wxT("Calc_pict/x^y.png"), wxBITMAP_TYPE_PNG);
  btns[15] = wxImage(wxT("Calc_pict/arowup.png"), wxBITMAP_TYPE_PNG);
  btns[16] = wxImage(wxT("Calc_pict/swap.png"), wxBITMAP_TYPE_PNG);
  btns[17] = wxImage(wxT("Calc_pict/shgL.png"), wxBITMAP_TYPE_PNG);
  btns[18] = wxImage(wxT("Calc_pict/shgR.png"), wxBITMAP_TYPE_PNG);
  btns[19] = wxImage(wxT("Calc_pict/sign.png"), wxBITMAP_TYPE_PNG);
  btns[20] = wxImage(wxT("Calc_pict/vo.png"), wxBITMAP_TYPE_PNG);
  btns[21] = wxImage(wxT("Calc_pict/vp.png"), wxBITMAP_TYPE_PNG);
  btns[22] = wxImage(wxT("Calc_pict/sp.png"), wxBITMAP_TYPE_PNG);
  btns[23] = wxImage(wxT("Calc_pict/p.png"), wxBITMAP_TYPE_PNG);
  btns[24] = wxImage(wxT("Calc_pict/pp.png"), wxBITMAP_TYPE_PNG);
  btns[25] = wxImage(wxT("Calc_pict/cx.png"), wxBITMAP_TYPE_PNG);
  btns[26] = wxImage(wxT("Calc_pict/f.png"), wxBITMAP_TYPE_PNG);
  btns[27] = wxImage(wxT("Calc_pict/bp.png"), wxBITMAP_TYPE_PNG);
  btns[28] = wxImage(wxT("Calc_pict/pnt.png"), wxBITMAP_TYPE_PNG);

  for (size_t i = 0; i < 29; i++) {
    btns[i].Scale(42, 42);
  }

  for (size_t i = 0; i < 10; i++) {
    if (i == 0) {
      new (bitmap_btns + i) wxBitmapButton(drawPane, 1000 + i,
                                           wxBitmap(btns[i]), wxPoint(49, 772));
    } else {
      switch (i % 3) {
        case 0:
          new (bitmap_btns + i)
              wxBitmapButton(drawPane, 1000 + i, wxBitmap(btns[i]),
                             wxPoint(212, 415 + 112 * (3 - i / 3)));
          break;

        case 1:
          new (bitmap_btns + i)
              wxBitmapButton(drawPane, 1000 + i, wxBitmap(btns[i]),
                             wxPoint(49, 415 + 112 * (2 - i / 3)));
          break;

        case 2:
          new (bitmap_btns + i)
              wxBitmapButton(drawPane, 1000 + i, wxBitmap(btns[i]),
                             wxPoint(131, 415 + 112 * (2 - i / 3)));
          break;
      }
    }
  }

  new (bitmap_btns + 10) wxBitmapButton(drawPane, BUTTON_10, wxBitmap(btns[10]),
                                        wxPoint(424, 528));
  new (bitmap_btns + 11) wxBitmapButton(drawPane, BUTTON_11, wxBitmap(btns[11]),
                                        wxPoint(424, 645));
  new (bitmap_btns + 12) wxBitmapButton(drawPane, BUTTON_12, wxBitmap(btns[12]),
                                        wxPoint(334, 528));
  new (bitmap_btns + 13) wxBitmapButton(drawPane, BUTTON_13, wxBitmap(btns[13]),
                                        wxPoint(334, 645));
  new (bitmap_btns + 14) wxBitmapButton(drawPane, BUTTON_14, wxBitmap(btns[14]),
                                        wxPoint(240, 307));
  new (bitmap_btns + 15) wxBitmapButton(drawPane, BUTTON_15, wxBitmap(btns[15]),
                                        wxPoint(424, 415));
  new (bitmap_btns + 16) wxBitmapButton(drawPane, BUTTON_16, wxBitmap(btns[16]),
                                        wxPoint(320, 409));
  new (bitmap_btns + 17) wxBitmapButton(drawPane, BUTTON_17, wxBitmap(btns[17]),
                                        wxPoint(162, 195));
  new (bitmap_btns + 18) wxBitmapButton(drawPane, BUTTON_18, wxBitmap(btns[18]),
                                        wxPoint(245, 195));
  new (bitmap_btns + 19) wxBitmapButton(drawPane, BUTTON_19, wxBitmap(btns[19]),
                                        wxPoint(248, 772));
  new (bitmap_btns + 20) wxBitmapButton(drawPane, BUTTON_20, wxBitmap(btns[20]),
                                        wxPoint(332, 195));
  new (bitmap_btns + 21) wxBitmapButton(drawPane, BUTTON_21, wxBitmap(btns[21]),
                                        wxPoint(354, 765));
  new (bitmap_btns + 22) wxBitmapButton(drawPane, BUTTON_22, wxBitmap(btns[22]),
                                        wxPoint(419, 187));
  new (bitmap_btns + 23) wxBitmapButton(drawPane, BUTTON_23, wxBitmap(btns[23]),
                                        wxPoint(160, 307));
  new (bitmap_btns + 24) wxBitmapButton(drawPane, BUTTON_24, wxBitmap(btns[24]),
                                        wxPoint(412, 307));
  new (bitmap_btns + 25)
      wxBitmapButton(drawPane, BUTTON_25, wxBitmap(btns[25]), wxPoint(40, 300));
  new (bitmap_btns + 26) wxBitmapButton(drawPane, BUTTON_26, wxBitmap(btns[26]),
                                        wxPoint(469, 772));
  new (bitmap_btns + 27) wxBitmapButton(drawPane, BUTTON_27, wxBitmap(btns[27]),
                                        wxPoint(330, 307));
  new (bitmap_btns + 28) wxBitmapButton(drawPane, BUTTON_28, wxBitmap(btns[28]),
                                        wxPoint(154, 772));

  for (size_t i = 0; i < 29; i++) {
    Connect(1000 + i, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(CalcFrame::pressOne));
  }

  gs = new wxGridSizer(3, 3, 3, 3);
  //  Создаем текстовый объект
  display =
      new wxTextCtrl(panel, -1, wxT("00"), wxPoint(100, 100), wxSize(50, 25));
  //  Устанавливаем размер шрифта
  display->SetFont(wxFontInfo(18));
  //  Устанавливаем цвет фона
  display->SetBackgroundColour(*wxCYAN);
  //  Добавляем display на sizer
  gs->Add(display, 0, wxEXPAND);
  //  можно и так добавлять. Но тогда не будет возмжности менять текст и
  //  атрибуты

  gs->Add(new wxTextCtrl(panel, -1, wxT("00000000"), wxPoint(0, 0),
                         wxSize(400, 50), wxTB_TOP));

  gs->Add(new wxTextCtrl(panel, -1, wxT("01"), wxPoint(123, 143),
                         wxSize(50, 50), wxTE_RIGHT),
          0, wxEXPAND);
  gs->Add(new wxTextCtrl(panel, -1, wxT("02"), wxPoint(11, 11), wxSize(50, 50),
                         wxTE_RIGHT),
          0, wxEXPAND);
  gs->Add(new wxTextCtrl(panel, -1, wxT("03"), wxPoint(-1, -1), wxSize(50, 50),
                         wxTE_RIGHT),
          0, wxEXPAND);

  //  Создаем еще один sizer который поместим на panel
  sizerP = new wxBoxSizer(wxVERTICAL);
  //  Помещаем на него таличный sizer
  sizerP->Add(gs, 1, wxEXPAND);
  //  Помещаем sizerP на panel.
  panel->SetSizer(sizerP);
  //  Добавляем panel на sizer справа от drawPane с каритинкой
  sizer->Add(panel, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 60);
  //  Устанавливаем sizer на окно
  SetSizer(sizer);
  // Окно раскроется в центре экрана
  Centre();
};

CalcFrame::~CalcFrame() {
  delete[] btns;
  delete[] bitmap_btns;
  Close(true);
};
void CalcFrame::Upd() {
  if (current_operand == LEFT_OPERAND) {
    display->Clear();
    display->AppendText(left_op);
  } else {
    display->Clear();
    display->AppendText(right_op);
  }
  display->SetFocus();
}
//  Функции при нажатии на кнопки
void CalcFrame::pressOne(wxCommandEvent& event) {
  int id = event.GetId();

  switch (id) {
    case BUTTON_0:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('0');
      } else {
        right_op.push_back('0');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_1:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('1');
      } else {
        right_op.push_back('1');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_2:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('2');
      } else {
        right_op.push_back('2');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_3:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('3');
      } else {
        right_op.push_back('3');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_4:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('4');
      } else {
        right_op.push_back('4');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_5:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('5');
      } else {
        right_op.push_back('5');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_6:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('6');
      } else {
        right_op.push_back('6');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_7:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('7');
      } else {
        right_op.push_back('7');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_8:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('8');
      } else {
        right_op.push_back('8');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_9:
      if (current_operand == LEFT_OPERAND) {
        left_op.push_back('9');
      } else {
        right_op.push_back('9');
      }
      CalcFrame::Upd();
      break;
    case BUTTON_10:
      current_operand = RIGHT_OPERAND;
      current_operation = ADD;
      display->SetFocus();
    case BUTTON_11:
      // Обработка события для кнопки минус
      break;
    case BUTTON_12:
      // Обработка события для кнопки умножить
      break;
    case BUTTON_13:
      // Обработка события для кнопки разделить
      break;
    case BUTTON_14:
      // Обработка события для кнопки очистить
      break;
    case BUTTON_15:
      // Обработка события для кнопки равно
      break;
    case BUTTON_16:
      // Обработка события для кнопки равно
      break;
    case BUTTON_17:
      // Обработка события для кнопки равно
      break;
    case BUTTON_18:
      // Обработка события для кнопки равно
      break;
    case BUTTON_19:
      // Обработка события для кнопки равно
      break;
    case BUTTON_20:
      // Обработка события для кнопки равно
      break;
    case BUTTON_21:
      // Обработка события для кнопки равно
      break;
    case BUTTON_22:
      // Обработка события для кнопки равно
      break;
    case BUTTON_23:
      // Обработка события для кнопки равно
      break;
    case BUTTON_24:
      // Обработка события для кнопки равно
      break;
    case BUTTON_25:
      // Обработка события для кнопки равно
      break;
    case BUTTON_26:
      // Обработка события для кнопки равно
      break;
    case BUTTON_27:
      // Обработка события для кнопки равно
      break;
    case BUTTON_28:
      // Обработка события для кнопки равно
      break;
    case BUTTON_29:
      // Обработка события для кнопки равно
      break;

    default:
      break;
  }
}

void CalcFrame::pressSec(wxCommandEvent& event) {
  wxMessageBox(wxT("Нажали на минус"));
}
// void CalcFrame::add(wxCommandEvent& event) {
//
//     display = wxDynamicCast(FindWindowById(BUTTON_10), wxTextCtrl);
//     wxString strValue = display->GetValue();
//     double value = wxAtof(strValue);
//
//     wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);
//     int id = button->GetId();
//
//     if (id == BUTTON_10) {
//         wxString strValue2 = display->GetValue();
//         double value2 = wxAtof(strValue2);
//         display->SetValue(wxString::Format(wxT("%f"), value + value2));
//     }
// }

class CalcApp : public wxApp {
  CalcFrame* frame;

 public:
  bool OnInit() {
    frame = new CalcFrame(wxT("БК-21"));
    frame->Show();
    //  Главное окно долно быть сверху и будет убираться последним
    SetTopWindow(frame);
    return true;
  }

  int OnExit() {
    // wxMessageBox(wxT("Все удалаяем"));

    return 0;
  }
};

IMPLEMENT_APP(CalcApp)