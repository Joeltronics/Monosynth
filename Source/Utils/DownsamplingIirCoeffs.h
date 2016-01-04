#ifndef DOWNSAMPLING_IIR_COEFFS_H
#define DOWNSAMPLING_IIR_COEFFS_H

/*
This file is generated from Python script by Joel Geddert

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

Downsampling FIR coefficients

DF1:
y[n] = b[0]*x[n] +
b[1]*x[n-1] + a[1]*y[n-1] +
b[2]*x[n-2] + a[2]*y[n-2] + ...

DF2:
w[n] =      x[n] - a[1]*w[n-1] - a[2]*w[n-2] - ...
y[n] = b[0]*w[n] + b[1]*w[n-1] + b[2]*w[n-2] + ...
*/

/***** 176 to 44 kHz *****/
// Elliptic (Cauer), order 10
// Max ripple < 20 kHz: -1.00 dB
// Max aliasing below 17.5 kHz: -93.66 dB
// Max aliasing 17.5-20 kHz: -85.99 dB

// Unfactored:

static const size_t order_176_44 = 10;

// Denominator (feedback) coeffs:
static const float a_176_44[11] = {
	1.0f,
	-7.997036833602538f,
	29.9694327934464f,
	-69.05517593292562f,
	108.09230921362953f,
	-119.92545220670533f,
	95.4270937455359f,
	-53.75711516595308f,
	20.520821603898934f,
	-4.7964889560109265f,
	0.5219654945958871f,
};

// Numerator (feed-forward) coeffs:
static const float b_176_44[11] = {
	9.264556736788482e-05f,
	-0.0002195390088530659f,
	0.0004431357041097709f,
	-0.00048332469544131796f,
	0.0005584258399206336f,
	-0.00046740152829610163f,
	0.0005584258399206331f,
	-0.00048332469544131807f,
	0.00044313570410977113f,
	-0.00021953900885306592f,
	9.264556736788479e-05f,
};

// Factored into biquad sections:

static const size_t nBiquad_176_44 = 5;
static const float biquad_176_44[5][6] = {
	{ 9.264556736788482e-05f, 0.00012893903529708728f, 9.264556736788482e-05f,
	1.0f, -1.734377334987571f, 0.7694255664427803f },
	{ 1.0f, -0.3138941966792076f, 0.9999999999999999f,
	1.0f, -1.6635363980453137f, 0.822252247205076f },
	{ 1.0f, -0.9690310174164505f, 0.9999999999999998f,
	1.0f, -1.5777755937826328f, 0.8893857735102974f },
	{ 1.0f, -1.1998385042606627f, 1.0f,
	1.0f, -1.5197399075207612f, 0.9436627645940776f },
	{ 1.0f, -1.2786471515926672f, 1.0f,
	1.0f, -1.5016075992662576f, 0.9830217230771731f },
};

/***** 192 to 48 kHz *****/
// Elliptic (Cauer), order 8
// Max ripple < 20 kHz: -1.00 dB
// Max aliasing below 17.5 kHz: -88.05 dB
// Max aliasing 17.5-20 kHz: -83.43 dB

// Unfactored:

static const size_t order_192_48 = 8;

// Denominator (feedback) coeffs:
static const float a_192_48[9] = {
	1.0f,
	-6.531878884370736f,
	19.44881164882814f,
	-34.34801015217284f,
	39.26595963418354f,
	-29.7155240615078f,
	14.530046111393297f,
	-4.197583426992193f,
	0.5489824592352529f,
};

// Numerator (feed-forward) coeffs:
static const float b_192_48[9] = {
	0.00015863400974422122f,
	-0.00019154971775019837f,
	0.0004096302608204871f,
	-0.00022224908848402026f,
	0.0004070364367468297f,
	-0.0002222490884840197f,
	0.00040963026082048686f,
	-0.00019154971775019847f,
	0.0001586340097442213f,
};

// Factored into biquad sections:

static const size_t nBiquad_192_48 = 4;
static const float biquad_192_48[4][6] = {
	{ 0.00015863400974422122f, 0.00021243683965012147f, 0.00015863400974422122f,
	1.0f, -1.7247344048354312f, 0.7623871756486466f },
	{ 1.0f, -0.38549577665309026f, 1.0f,
	1.0f, -1.657063013671468f, 0.8238908616351945f },
	{ 1.0f, -0.9903105098823346f, 1.0000000000000002f,
	1.0f, -1.58643914637809f, 0.9017658243729112f },
	{ 1.0f, -1.1708516341191744f, 1.0f,
	1.0f, -1.5636423194857456f, 0.9692134406015533f },
};

/***** 176 to 88 kHz *****/
// Butterworth, order 6
// Max ripple < 20 kHz: -0.66 dB
// Max aliasing below 17.5 kHz: -102.68 dB
// Max aliasing 17.5-20 kHz: -95.19 dB

// Unfactored:

static const size_t order_176_88 = 6;

// Denominator (feedback) coeffs:
static const float a_176_88[7] = {
	1.0f,
	-2.862952298805565f,
	3.8771304588732054f,
	-2.992628510635404f,
	1.3694804054277756f,
	-0.34786528134291383f,
	0.038076188846317915f,
};

// Numerator (feed-forward) coeffs:
static const float b_176_88[7] = {
	0.0012693900369283775f,
	0.007616340221570265f,
	0.01904085055392566f,
	0.02538780073856755f,
	0.01904085055392566f,
	0.007616340221570265f,
	0.0012693900369283775f,
};

// Factored into biquad sections:

static const size_t nBiquad_176_88 = 3;
static const float biquad_176_88[3][6] = {
	{ 0.0012693900369283775f, 0.002538780073856755f, 0.0012693900369283775f,
	1.0f, -0.8047286624949015f, 0.174139230161371f },
	{ 1.0f, 2.0f, 1.0f,
	1.0f, -0.9048446191477673f, 0.3202134011829725f },
	{ 1.0f, 2.0f, 1.0f,
	1.0f, -1.1533790171628964f, 0.6828374760474021f },
};

/***** 192 to 96 kHz *****/
// Butterworth, order 6
// Max ripple < 20 kHz: -0.49 dB
// Max aliasing below 17.5 kHz: -110.77 dB
// Max aliasing 17.5-20 kHz: -103.41 dB

// Unfactored:

static const size_t order_192_96 = 6;

// Denominator (feedback) coeffs:
static const float a_192_96[7] = {
	1.0f,
	-3.041025474290884f,
	4.2806119839971934f,
	-3.411799519197676f,
	1.6027911293521484f,
	-0.41647777576478273f,
	0.04648961610223508f,
};

// Numerator (feed-forward) coeffs:
static const float b_192_96[7] = {
	0.0009467181280974f,
	0.0056803087685844f,
	0.014200771921461f,
	0.018934362561948002f,
	0.014200771921461f,
	0.0056803087685844f,
	0.0009467181280974f,
};

// Factored into biquad sections:

static const size_t nBiquad_192_96 = 3;
static const float biquad_192_96[3][6] = {
	{ 0.0009467181280974f, 0.0018934362561948f, 0.0009467181280974f,
	1.0f, -0.8596779857477461f, 0.19635399024541303f },
	{ 1.0f, 2.0f, 1.0f,
	1.0f, -0.9634061424764916f, 0.34070524299419447f },
	{ 1.0f, 2.0f, 1.0f,
	1.0f, -1.2179413460666464f, 0.6949241616142223f },
};

#endif
