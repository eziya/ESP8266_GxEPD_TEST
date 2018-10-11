#include "Arduino.h"

/* GxEPD 관련 Include 파일 */
#include <GxEPD.h>
#include <GxGDEP015OC1/GxGDEP015OC1.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

/*DSDIGIT 폰트는 Adafruit GFX Library에 FontConverter 를 사용해서 생성 후 GFX 라이브러리 Fonts 폴더에 추가 필요 */
#include <Fonts/DSDIGIT9pt7b.h>
#include <Fonts/DSDIGIT12pt7b.h>
#include <Fonts/DSDIGIT18pt7b.h>
#include <Fonts/DSDIGIT24pt7b.h>
#include <Fonts/DSDIGIT30pt7b.h>
#include <GxGDEP015OC1/BitmapExamples.h>

#include "ImageData.h"

#define DEMO_DELAY 30

/* BUSY -> GPIO4, RST -> GPIO2, DC -> GPIO0, CS -> GPIO5, CLK -> GPIO14, DIN -> GPIO13, GND -> GND, 3.3V -> 3.3V */
/* Default 예제에서는 CS(SS)에 GPIO15를 사용하나 NodeMCU 에서 업데이트 모드로 들어가는데 문제가 있어 GPIO5로 변경 필요 */
GxIO_Class io(SPI, SS, 0, 2);
GxEPD_Class display(io);

void setup()
{
	/* Debug용 시리얼 115200 bps */
	Serial.begin(115200);

	/* EPD 진단용 시리얼 115200 bps */
	display.init(115200);

	Serial.println("Setup OK");
}

void loop()
{
	showBitmapExample();
	drawCornerTest();

	showFont("DSDIGIT9pt7b", &DSDIGIT9pt7b);
	showFont("DSDIGIT12pt7b", &DSDIGIT12pt7b);
	showFont("DSDIGIT18pt7b", &DSDIGIT18pt7b);
	showFont("DSDIGIT24pt7b", &DSDIGIT24pt7b);
	showFont("DSDIGIT30pt7b", &DSDIGIT30pt7b);
	showPartialUpdatePaged();

	delay(1000);
}

/* Bitmap 그리기 예제 */
void showBitmapExample()
{
	/* 버퍼를 흰색으로 Clear */
	display.fillScreen(GxEPD_WHITE);

	/* Bitmap 그리기, bm_invert 사용시 0xFF 가 흰색, bm_normal 사용시 0xFF 가 검은색 */
	display.drawBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK, GxEPD::bm_invert | GxEPD::bm_flip_x);

	/* Display 출력 */
	display.update();

	delay(5000);

	/* Boat 이미지 출력 */
	showBoat();
}

/* Bitmap 그리기 및 이동 예제 */
void showBoat()
{
	/* 위치 X, Y 값 설정 */
	uint16_t x = (display.width() - 64) / 2;
	uint16_t y = 5;

	/* Display Clear */
	display.fillScreen(GxEPD_WHITE);

	/* Bitmap 그리기 */
	display.drawBitmap(gImage_Boat, x, y, 64, 180, GxEPD_BLACK, GxEPD::bm_invert | GxEPD::bm_flip_x);
	display.update();
	delay(500);

	/* bm_invert: 색상반전, bm_flip_x: x축 회전, bm_flip_y: y 축 회전 */
	uint16_t forward = GxEPD::bm_invert | GxEPD::bm_flip_x;
	uint16_t reverse = GxEPD::bm_invert | GxEPD::bm_flip_x | GxEPD::bm_flip_y;

	/* Y축을 기준으로 그림의 위치를 변경하며 Bitmap 그리기 */
	for (; y + 180 + 5 <= display.height(); y += 5)
	{
		display.fillScreen(GxEPD_WHITE);
		display.drawBitmap(gImage_Boat, x, y, 64, 180, GxEPD_BLACK, forward);
		display.updateWindow(0, 0, display.width(), display.height());
		delay(500);
	}

	delay(1000);
	for (; y >= 5; y -= 5)
	{
		display.fillScreen(GxEPD_WHITE);
		display.drawBitmap(gImage_Boat, x, y, 64, 180, GxEPD_BLACK, reverse);
		display.updateWindow(0, 0, display.width(), display.height());
		delay(1000);
	}

	display.update();
	delay(1000);
}

/* 선택한 폰트를 출력하는 예제 */
void showFont(const char name[], const GFXfont* font)
{
	display.fillScreen(GxEPD_WHITE);

	/* 텍스트 색상 설정 */
	display.setTextColor(GxEPD_BLACK);

	/* 폰트 설정 */
	display.setFont(font);

	/* 커서 위치 설정 */
	display.setCursor(0, 0);

	/* 텍스트 출력 */
	display.println();
	display.println(name);
	display.println(" !\"#$%&'()*+,-./");
	display.println("0123456789:;<=>?");
	display.println("@ABCDEFGHIJKLMNO");
	display.println("PQRSTUVWXYZ[\\]^_");
	display.println("`abcdefghijklmno");
	display.println("pqrstuvwxyz{|}~ ");

	/* Display 출력 */
	display.update();
	delay(5000);
}

/* 4개 코너에 4가지 크기의 사각형 그리기 예제 */
void drawCornerTest()
{
	/* 현재 Rotation 값 확인 */
	uint8_t rotation = display.getRotation();

	/* 4 방향 Rotation 테스트 */
	for (uint16_t r = 0; r < 4; r++)
	{
		/* Rotation 설정 */
		display.setRotation(r);

		display.fillScreen(GxEPD_WHITE);

		/* 채워진 사각형 그리기 8, 16, 24, 32 사이즈 */
		display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
		display.fillRect(display.width() - 18, 0, 16, 16, GxEPD_BLACK);
		display.fillRect(display.width() - 25, display.height() - 25, 24, 24, GxEPD_BLACK);
		display.fillRect(0, display.height() - 33, 32, 32, GxEPD_BLACK);

		/* Display 출력 */
		display.update();
		delay(5000);
	}

	/* Rotation 값 복구 */
	display.setRotation(rotation);
}

/* drawPagedToWindow 의 Callback 함수로 호출되며, v 값에 따라서 상자를 검은색 또는 흰색으로 채우는 함수 */
void showBlackBoxCallback(uint32_t v)
{
	uint16_t box_x = 10;
	uint16_t box_y = 15;
	uint16_t box_w = 70;
	uint16_t box_h = 20;
	display.fillRect(box_x, box_y, box_w, box_h, v);
}

/* drawPagedToWindow 의 Callback 함수로 호출되며, v값을 100으로 나누어서 텍스트를 출력하는 함수 */
void showValueBoxCallback(const uint32_t v)
{
	uint16_t box_x = 10;
	uint16_t box_y = 15;
	uint16_t box_w = 70;
	uint16_t box_h = 20;
	uint16_t cursor_y = box_y + box_h - 6;
	display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
	display.setCursor(box_x, cursor_y);
	display.print(v / 100);
	display.print(v % 100 > 9 ? "." : ".0");
	display.print(v % 100);
}

/* Partial 업데이트 예제 */
void showPartialUpdatePaged()
{
	/* Partial 동작 영역 */
	uint16_t box_x = 10;
	uint16_t box_y = 15;
	uint16_t box_w = 70;
	uint16_t box_h = 20;

	uint32_t value = 1395;

	/* Display 설정 폰트, 색상, Rotation */
	display.setFont(&DSDIGIT9pt7b);
	display.setTextColor(GxEPD_BLACK);
	display.setRotation(0);

	/* Partial 업데이트로 Bitmap 그리기 */
	display.drawBitmap(BitmapExample1, sizeof(BitmapExample1), GxEPD::bm_flip_x | GxEPD::bm_partial_update);
	delay(1000);

	/* 4방향 회전하면서 숫자 출력하기 */
	for (uint16_t r = 0; r < 4; r++)
	{
		display.setRotation(r);
		for (uint16_t i = 1; i <= 4; i++)
		{
			uint32_t v = value * i;
			display.drawPagedToWindow(showValueBoxCallback, box_x, box_y, box_w, box_h, v);
			delay(500);
		}
		delay(1000);

		/* 문자열을 출력했던 영역 Clear */
		display.drawPagedToWindow(showBlackBoxCallback, box_x, box_y, box_w, box_h, GxEPD_WHITE);
	}

	display.setRotation(0);
	display.powerDown();
}
