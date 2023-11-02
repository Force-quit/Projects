#include <iostream>
#include <Windows.h>

int main()
{
	Sleep(2000);
	COLORREF centerColor;
	HWND hd = GetForegroundWindow();
	RECT Rect;
	std::cout << "Starting\n";
	int i{};
	if (GetWindowRect(hd, &Rect))
	{
		int middleX{ Rect.right / 2 };
		int middleY{ Rect.bottom / 2 };
		HDC hdc_ = GetDC(hd);
		const auto range{ 5 };
		std::cout << Rect.right << "," << Rect.bottom << "\n";
		while (true)
		{
			for (int y{ middleY - range }; y < middleY + range; ++y)
			{
				for (int x{ middleX - range }; x < middleX + range; ++x)
				{
					centerColor = GetPixel(hdc_, x, y);
					auto r{ int(GetRValue(centerColor)) };
					auto g{ int(GetGValue(centerColor)) };
					auto b{ int(GetBValue(centerColor)) };

					if (r == 0 and g == 0 and b == 0)
					{
						SendMessage(hd, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(15, 15));
						Sleep(50);
						SendMessage(hd, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(15, 15));
						Sleep(100);
					}
				}
			}
		}

		ReleaseDC(hd, hdc_); // You should call this when you've finised with the DC!
	}

	std::cout << "Done";
	std::cin.get();
}