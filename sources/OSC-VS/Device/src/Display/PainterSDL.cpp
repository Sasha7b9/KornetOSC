#include "../Application.h"


#define uint    unsigned int
#define int8    signed char
#define uint8   unsigned char
#define int16   signed short
#define uint16  unsigned short
#define uint    unsigned int
#define uchar   unsigned char
#define pString const char * const

#include "../../Display/Painter.h"

#include <SDL.h>

#include <wx/display.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SDL_Renderer *renderer = nullptr;
static SDL_Window *window = nullptr;
static SDL_Texture *texture = nullptr;

static wxButton *btnDisplay = nullptr;
static wxButton *btnMeasures = nullptr;
static wxButton *btnService = nullptr;
static wxButton *btnMemory = nullptr;
static wxButton *btnFunction = nullptr;

static wxButton *btnEnter = nullptr;
static wxButton *btnLeft = nullptr;
static wxButton *btnRight = nullptr;
static wxButton *btnUp = nullptr;
static wxButton *btnDown = nullptr;

static wxButton *btnF1 = nullptr;
static wxButton *btnF2 = nullptr;
static wxButton *btnF3 = nullptr;
static wxButton *btnF4 = nullptr;
static wxButton *btnF5 = nullptr;

static wxButton *btnStart = nullptr;

/// Цвета
static uint colors[256];


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Создаёт окно приложения. Возвращает хэндл виджета для отрисовки
static HANDLE CreateFrame();
/// Установить оптимальную позицию для окна приложения
static void SetPosition(Frame *frame);
/// Получить разрешение максимального имеющегося в системе монитора
static wxRect GetMaxDisplay();
/// Создаёт все кнопки
static void CreateButtons(Frame *frame);
/// Создаёт одну кнопку
static wxButton *CreateButton(Frame *frame, const wxPoint &pos, const wxSize &size, char *title);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Painter::Init()
{
    HANDLE handle = CreateFrame();

    window = SDL_CreateWindowFrom(handle);

    if (window == nullptr)
    {
        std::cout << "SDL_CreateWindowFrom() Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "Create SDL window is ok";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::BeginScene(Color color)
{
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_RENDERER_ACCELERATED, 320, 240);

    SDL_SetRenderTarget(renderer, texture);
    SetColor(color);
    SDL_RenderClear(renderer);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::EndScene()
{
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Rect rect = {0, 0, 320, 240};

    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetPoint(int x, int y, Color color /* = Color::NUMBER */)
{
    SetColor(color);
    SDL_Rect rect = { x, y, 1, 1 };
    SDL_RenderFillRect(renderer, &rect);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColorValue(Color color, uint value)
{
    colors[color.value] = value;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLineArray(int x, int numLines, uint8 *y0y1, Color color)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::Draw10SymbolsInRect(int x, int y, char eChar)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawTesterData(uint8 mode, Color color, uint8 x[240], uint8 y[240])
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVPointLine(int x, int y0, int y1, float delta)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHPointLine(int y, int x0, int x1, float delta)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawMultiHPointLine(int numLines, int x, uint8 y[], int delta, int count, Color color /* = Color::NUMBER */)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawMultiVPointLine(int numLines, int y, uint16 x[], int delta, int count, Color color /* = Color::NUMBER */)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawTextRelativelyRight(int xRight, int y, const char *text, Color color /* = Color::NUMBER */)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawBigText(int x, int y, int size, const char *text, Color color /* = Color::NUMBER */)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawStringInCenterRectOnBackgroundC(int x, int y, int width, int height, const char *text, Color colorText, int widthBorder, Color colorBackground)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextOnBackground(int x, int y, const char *text, Color colorBackground)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawFormatText(int x, int y, char *format, ...)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextInRectWithTransfers(int x, int y, int width, int height, const char *text)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::Draw4SymbolsInRect(int x, int y, char eChar, Color color /* = Color::NUMBER */)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawLine(int x0, int y0, int x1, int y1, Color color)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextInBoundedRectWithTransfers(int x, int y, int width, const char *text, Color colorBackground, Color colorFill)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawStringInCenterRectAndBoundItC(int x, int y, int width, int height, const char *text, Color colorBackground, Color colorFill)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawChar(int x, int y, char symbol, Color color /* = Color::NUMBER */)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawFormText(int x, int y, Color color, pString text, ...)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawTextWithLimitation(int x, int y, const char *text, int limitX, int limitY, int limitWidth, int limitHeight)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, float y0, float y1, Color color)
{
    DrawVLine((int)x, (int)y0, (int)y1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawVLine(int x, int y0, int y1, Color color)
{
    SetColor(color);

    SDL_Rect rect = {x, y0, 1, y1 - y0};

    SDL_RenderFillRect(renderer, &rect);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawHLine(int y, int x0, int x1, Color color)
{
    SetColor(color);

    SDL_Rect rect = {x0, y, x1 - x0, 1};

    SDL_RenderFillRect(renderer, &rect);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetColor(Color color)
{
    if (color != Color::NUMBER)
    {
        uint value = colors[color.value];
        uint8 blue = (uint8)value;
        uint8 green = (uint8)(value >> 8);
        uint8 red = (uint8)(value >> 16);
        SDL_SetRenderDrawColor(renderer, red, green, blue, 0x00);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetBrightnessDisplay(int16 brightness)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::ResetFlash()
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawStringInCenterRect(int x, int y, int width, int height, const char *text, Color color /* = Color::NUMBER */)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::DrawRectangle(int x, int y, int width, int height, Color color)
{
    SetColor(color);
    DrawVLine(x, y, y + height);
    DrawVLine(x + width, y, y + height);
    DrawHLine(y, x, x + width);
    DrawHLine(y + height, x, x + width);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::SetFont(Font::Type::E typeFont)
{

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int Painter::DrawText(int x, int y, const char *text, Color color /* = Color::NUMBER */)
{
    return x;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Painter::FillRegion(int x, int y, int width, int height, Color color)
{
    SetColor(color);

    SDL_Rect rect = {x, y, width, height};

    SDL_RenderFillRect(renderer, &rect);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void SetPosition(Frame *frame)
{
    wxSize size = { 329, 700 };

    frame->SetSize(size);
    frame->SetMinSize(size);
    frame->SetMaxSize(size);

    wxRect rect = GetMaxDisplay();

    frame->SetPosition({ rect.width / 2 - size.GetWidth() / 2, rect.height / 2 - size.GetHeight() / 2 });
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static wxRect GetMaxDisplay()
{
    wxRect result = {0, 0, 0, 0};

    for (int i = 0; i < wxDisplay::GetCount(); i++)
    {
        wxDisplay display(i);

        wxRect rect = display.GetClientArea();
        if (rect.width > result.width)
        {
            result.width = rect.width;
            result.height = rect.height;
        }
    }

    return result;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static HANDLE CreateFrame()
{
    Frame *frame = new Frame("");

    SetPosition(frame);

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *btnDisplay = new wxButton(frame, wxID_ANY, "", {10, 10}, {320, 240});
    btnDisplay->SetMaxSize({320, 240});

    sizer->Add(btnDisplay);

    frame->SetSizer(sizer);

    CreateButtons(frame);

    frame->Show(true);

    return btnDisplay->GetHandle();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void CreateButtons(Frame *frame)
{
    // Рисуем кнопки меню и функциональные

    wxButton *buttons[2][5] =
    {
        { btnF1,       btnF2,      btnF3,     btnF4,       btnF5 },
        { btnFunction, btnDisplay, btnMemory, btnMeasures, btnService }
    };

        
    char *titles[2][5] = 
    {
        { "F1",      "F2",      "F3",     "F4",        "F5" },
        { "Функция", "Дисплей", "Память", "Измерения", "Сервис" }
    };

    int x0 = 5;
    int y0 = 250;

    int dX = 5;
    int dY = 5;

    int width = 58;
    int height = 25;

    wxSize size = {width, height};

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            buttons[j][i] = CreateButton(frame, {x0 + (width + dX) * i, y0 + (height + dY) * j}, size, titles[j][i]);
        }
    }

    // Рисуем кнопки управления

    width = height = 25;
    x0 = 320 / 2 - width / 2;
    y0 = 240 + 100;

    size.SetWidth(width);
    size.SetHeight(height);

    btnEnter = CreateButton(frame, {x0, y0}, size, "E");
    btnLeft = CreateButton(frame, {x0 - dX - width, y0}, size, "L");
    btnRight = CreateButton(frame, {x0 + dX + width, y0}, size, "R");
    btnUp = CreateButton(frame, {x0, y0 - height - dY}, size, "U");
    btnDown = CreateButton(frame, {x0, y0 + height + dY}, size, "D");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static wxButton *CreateButton(Frame *frame, const wxPoint &pos, const wxSize &size, char *title)
{
    return new wxButton(frame, wxID_ANY, title, pos, size);
}
