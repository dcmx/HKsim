#ifndef COLOR_H
#define COLOR_H

namespace nx {
namespace colors {
class Color {
public:
	double r, g, b, a;
	inline Color() :
			r(0.0), g(0.0), b(0.0), a(0.0) {
	}
	inline Color(double r, double g, double b) :
			r(r), g(g), b(b), a(1.0) {
	}
	inline Color(double r, double g, double b, double a) :
			r(r), g(g), b(b), a(a) {
	}
	inline Color(int r, int g, int b) :
			r((double) r / 255.0), g((double) g / 255.0), b((double) b / 255.0), a(1.0) {
	}
	inline Color(int r, int g, int b, int a) :
			r((double) r / 255.0), g((double) g / 255.0), b((double) b / 255.0), a((double) a / 100.0) {
	}
	inline Color(const Color& color) :
			r(color.r), g(color.g), b(color.b), a(color.a) {
	}
	void set() const;
	void setAsBackground() const;
};

extern const Color red;
extern const Color green;
extern const Color blue;
extern const Color yellow;
extern const Color cyan;
extern const Color magenta;
extern const Color white;
extern const Color lightgrey;
extern const Color darkgrey;
extern const Color black;

}
}

#endif
