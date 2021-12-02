#include "Zion/TextDraw.hh"
#include "Zion/Client.hh"
#include "Zion/List.hh"
#include "Zion/Cursor.hh"
#include "Zion/Util.hh"
#include "Game/CFont.h"
#include "Game/RenderWare.h"
#include "Game/CMessages.h"

static const float ps2Width = 640.0F;
static const float ps2Height = 448.0F;
static bool selectTextDraw = false;
static unsigned int hoverColor = 0;

static Zion::List<Zion::TextDraw *> textDraws;

void Zion::TextDraw::Add(Transmit t, int id)
{
    while(textDraws.GetLength() <= id)
        textDraws.Push(nullptr);

    textDraws[id] = new TextDraw(t, id);
}

void Zion::TextDraw::Remove(int id)
{
    if(id >= textDraws.GetLength())
        return;

    TextDraw *textDraw = textDraws[id];
    if(textDraw == nullptr)
        return;

    delete textDraw;
    textDraws[id] = nullptr;

    if(id == textDraws.GetLength() - 1) {
        while(textDraws.GetLength() > 0 && textDraws.Back() == nullptr)
            textDraws.Pop();
    }
}

void Zion::TextDraw::Render_()
{
    for(unsigned long index = 0; index < textDraws.GetLength(); index++)
    {
        TextDraw *textDraw = textDraws[index];
        if(textDraw != nullptr)
            textDraw->Render();
    }
}

void Zion::TextDraw::Process_()
{
    if(selectTextDraw)
    {
        Cursor::show = true;
        Cursor::allowMovement = true;

        for(unsigned long index = 0; index < textDraws.GetLength(); index++)
        {
            TextDraw *textDraw = textDraws[index];
            if(textDraw != nullptr)
                textDraw->Process();
        }
    }
}

void Zion::TextDraw::SetString_(int id, const char *string)
{
    TextDraw *textDraw = textDraws[id];
    if(textDraw == nullptr)
        return;

    textDraw->SetString(string);
}

Zion::TextDraw::TextDraw(Transmit t, int id)
{
    this->t = t;
    this->id = id;
    this->string = nullptr;
    this->hover = false;
}

void Zion::TextDraw::Render()
{
    const float horizontalScale = *(float *)0x859520;
    const float verticalScale = *(float *)0x859524;

    CFont::SetScale(
        RsGlobal.maximumWidth * horizontalScale * this->t.letterWidth,
        RsGlobal.maximumHeight * verticalScale * this->t.letterHeight * 0.5F);

    if(selectTextDraw && this->hover)
        *CFont::m_Color = hoverColor;
    else
        *CFont::m_Color = this->t.letterColor;

    CFont::SetJustify(false);

    if(this->t.right)
        CFont::SetOrientation(ALIGN_RIGHT);
    else if(this->t.center)
        CFont::SetOrientation(ALIGN_CENTER);
    else
        CFont::SetOrientation(ALIGN_LEFT);

    CFont::SetWrapx(RsGlobal.maximumWidth * this->t.lineWidth * horizontalScale);
    CFont::SetCentreSize(RsGlobal.maximumHeight * this->t.lineHeight * verticalScale);
    CFont::SetBackground(this->t.box, false);
    CFont::SetBackgroundColor(this->t.boxColor);
    CFont::SetProportional(this->t.proportional);
    CFont::SetDropColor(this->t.backgroundColor);

    if(this->t.outline)
        CFont::SetEdge(this->t.outline);
    else
        CFont::SetDropShadowPosition(this->t.shadow);

    CFont::SetFontStyle(this->t.style);

    float x = RsGlobal.maximumWidth - ((ps2Width - this->t.x) * (RsGlobal.maximumWidth * horizontalScale));
    float y = RsGlobal.maximumHeight - ((ps2Height - this->t.y) * (RsGlobal.maximumHeight * verticalScale));

    CFont::PrintString(x, y, this->string);

    if(this->t.right)
    {
        this->area.x1 = x - (this->t.lineWidth - x);
        this->area.x2 = x;
        this->area.y1 = y;
        this->area.y2 = y + this->t.lineHeight;
    }
    else if(this->t.center)
    {
        this->area.x1 = x - (this->t.lineHeight * 0.5f);
        this->area.x2 = this->area.x1 + this->t.lineHeight;
        this->area.y1 = y;
        this->area.y2 = y + this->t.lineWidth;
    }
    else
    {
        this->area.x1 = x;
        this->area.x2 = this->t.lineWidth;
        this->area.y1 = y;
        this->area.y2 = y + this->t.lineHeight;
    }
}

void Zion::TextDraw::Process()
{
    if(this->t.selectable)
    {
        POINT cursorPosition;
        GetCursorPos(&cursorPosition);

        if(cursorPosition.x >= this->area.x1 && cursorPosition.x <= this->area.x2)
        {
            if(cursorPosition.y >= this->area.y1 && cursorPosition.y <= this->area.y2)
            {
                if(Util::IsKeyPressed(VK_LBUTTON))
                    Client::SendTextDrawClick(this->id);

                this->hover = true;
            }
            else
                this->hover = false;
        }
        else
            this->hover = false;
    }
}

void Zion::TextDraw::SetString(const char *string)
{
    char buffer[512];
    strcpy(buffer, string);
    CMessages::InsertPlayerControlKeysInString(buffer);

    delete[] this->string;
    this->string = strdup(buffer);
}

void Zion::TextDraw::SelectTextDraw(bool x)
{
    selectTextDraw = x;
    Cursor::show = x;
    Cursor::allowMovement = x;
}

void Zion::TextDraw::SetHoverColor(unsigned int hoverColor)
{
    ::hoverColor = hoverColor;
}