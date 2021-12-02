#pragma once
#include "Vector.hh"

namespace Zion
{
    class TextDraw
    {
        public:
            struct Transmit
            {
                struct
                {
                    unsigned char box : 1;
                    unsigned char left : 1;
                    unsigned char right : 1;
                    unsigned char center : 1;
                    unsigned char proportional : 1;
                    unsigned char padding : 3;
                };

                float letterWidth;
                float letterHeight;
                unsigned int letterColor;
                float lineWidth;
                float lineHeight;
                unsigned int boxColor;
                unsigned char shadow;
                unsigned char outline;
                unsigned int backgroundColor;
                unsigned char style;
                unsigned char selectable;
                float x;
                float y;
                unsigned short model;
                Vector3F rotation;
                float zoom;
                unsigned short color1;
                unsigned short color2;
            } __attribute__((packed));

            static void Add(Transmit t, int id);
            static void Remove(int id);
            static void Render_();
            static void Process_();
            static void SetString_(int id, const char *string);
            static void SelectTextDraw(bool x);
            static void SetHoverColor(unsigned int hoverColor);

        private:
            TextDraw(Transmit t, int id);

            void Render();
            void Process();
            void SetString(const char *string);

            char *string;
            int id;
            Transmit t;
            struct {
                float x1;
                float y1;
                float x2;
                float y2;
            } area;
            bool hover;
    };
};