#include <stdint.h>
//#include "ov769x.h"

// Captured from working BK7252, modified to work with MCLK 24MHz

// Comments provided by Sonnet 4.5, could be wrong!

const uint8_t ov769x_init_table[][2] = {
    // ========================================
    // INITIALIZATION SEQUENCE (I2C Wake-up)
    // ========================================

    // ========================================
    // BASIC SENSOR CONFIGURATION
    // ========================================
    {0x0c, 0x00},  // REG0C: Image orientation and data format control
                   // Default: 0x00
                   // Bit[7]=1: Vertical flip enabled
                   // Bit[6]=1: Horizontal mirror enabled  
                   // Bit[4]=1: YU/YV swap in YUV format
                   // Bit[2]=1: Clock output pin active (data pins output state)
                   // Bit[1]=1: VSYNC, HREF, PCLK output state active

    {0x48, 0x44},  // ANA1: Analog control (reserved)
                   // Default: 0x40 -> 0x44 (minor adjustment)

    {0x49, 0x0d},  // Voltage 2.8V

    {0x41, 0x43},  // Reserved register (0x40-0x47 range)

    // ========================================
    // ISP MODULE ENABLES
    // ========================================
    {0x81, 0xff},  // REG81: ISP module enable control
                   // Default: 0x41 -> 0xFF (Enable ALL ISP modules)
                   // Bit[5]=1: SDE (Special Digital Effects) enabled
                   // Bit[4]=1: UV adjust enabled
                   // Bit[3]=1: Vertical scaling enabled
                   // Bit[2]=1: Horizontal scaling enabled
                   // Bit[1]=1: UV average enabled
                   // Bit[0]=1: Color matrix enabled

    // ========================================
    // EXPOSURE & BANDING CONTROL
    // ========================================
    {0x21, 0x67},  // AECGM: Banding filter maximum step
                   // Default: 0x44 -> 0x67
                   // Adjusts banding filter for 50Hz/60Hz light sources

    // ========================================
    // WINDOWING & ARRAY CONTROL
    // ========================================
    {0x16, 0x03},  // REG16: Array control
                   // Default: 0x08 -> 0x03
                   // Bit[6]=0: Horizontal sensor size LSB
                   // Bit[5]=0: Roff1 - vertical window start adjustment
                   // Bit[4]=0: Hoff1 - horizontal window start adjustment
                   // Lower bits affect windowing offset

    {0x39, 0x80},  // Reserved register (0x39-0x3D range)

    // ========================================
    // CLOCK CONFIGURATION
    // ========================================
    {0x11, 0x00},  // CLKRC: Clock control (matches default)
                   // Bit[6]=0: Use clock prescaler (not external direct)
                   // Bit[5:0]=0: No clock division (F_internal = F_input)

    // ========================================
    // OUTPUT FORMAT CONFIGURATION
    // ========================================
    {0x12, 0x00},  // REG12: Output format control
                   // Default: 0x11 -> 0x00
                   // Bit[7]=0: No system reset
                   // Bit[6]=0: Skip model disabled
                   // Bit[5]=0: ITU656 protocol disabled
                   // Bit[1:0]=00: YUV output format

    {0x82, 0x03},  // REG82: ISP output selection
                   // Default: 0x00 -> 0x03
                   // Bit[1:0]=11: YUV422 output selected

    // ========================================
    // WINDOWING & SCALING (Input/Output Size)
    // ========================================
    {0xd0, 0x48},  // REGD0: Boundary offset (matches default)
                   // Bit[7:4]=0x4: WIN_VOFF (vertical offset = 4)
                   // Bit[3:0]=0x8: WIN_HOFF (horizontal offset = 8)

    {0x80, 0x7e},  // REG80: ISP module enables
                   // Default: 0x7E
                   // Bit[7]=0: VarioPixel disabled
                   // Bit[6]=1: Color interpolation enabled
                   // Bit[5]=1: Black pixel correction enabled
                   // Bit[4]=1: White pixel correction enabled
                   // Bit[3]=1: Gamma enabled
                   // Bit[2]=1: AWB gain enabled
                   // Bit[1]=1: AWB enabled
                   // Bit[0]=1: Lens correction enabled (changed from default)

    // ========================================
    // PIXEL CLOCK CONFIGURATION
    // ========================================
    {0x3e, 0x30},  // REG3E: PCLK control
                   // Default: 0x20 -> 0x30
                   // Bit[6]=0: PCLK always output (not gated by HREF)
                   // Bit[4]=1: PCLK for YUV format (double rate vs RAW)

    {0x22, 0x00},  // REG22: Optical black control (matches default)



    // ========================================
    // SENSOR ARRAY WINDOWING
    // ========================================
    {0x17, 0x69},  // HSTART: Horizontal window start (matches default)
    {0x18, 0xa4},  // HSize: Horizontal sensor size
                   // Default: 0xA0 -> 0xA4
                   // Actual horizontal size = 2 × {0xA4, REG16[6]}
                   // Slightly larger horizontal window

    {0x19, 0x0c},  // VSTART: Vertical window start
                   // Default: 0x0E -> 0x0C
                   // Starts 2 lines earlier

    {0x1a, 0xf6},  // VSize: Vertical sensor size
                   // Default: 0xF0 -> 0xF6
                   // Actual vertical size = 2 × 0xF6 = 492 pixels
                   // Slightly larger vertical window

    // ========================================
    // SCALING CONFIGURATION (640x480 VGA)
    // ========================================
    // Input image size configuration
    {0xc8, 0x02},  // REGC8: IH[9:8] - Horizontal input size MSBs (matches default)
    {0xc9, 0x80},  // REGC9: IH[7:0] - Horizontal input = 640 (matches default)
    {0xca, 0x01},  // REGCA: IV[8] - Vertical input size MSB (matches default)
    {0xcb, 0xe0},  // REGCB: IV[7:0] - Vertical input = 480 (matches default)
    
    // Output image size configuration (same as input = no scaling)
    {0xcc, 0x02},  // REGCC: OH[9:8] - Horizontal output size MSBs (matches default)
    {0xcd, 0x80},  // REGCD: OH[7:0] - Horizontal output = 640 (matches default)
    {0xce, 0x01},  // REGCE: OV[8] - Vertical output size MSB (matches default)
    {0xcf, 0xe0},  // REGCF: OV[7:0] - Vertical output = 480 (matches default)

    // ========================================
    // LENS CORRECTION (LENC)
    // ========================================
    {0x85, 0x10},  // LCC0: Lens correction control
                   // Default: 0x00 -> 0x10
                   // Bit[7]=0: LENC disabled initially
                   // Bit[4]=1: LENC gain enabled

    {0x86, 0x00},  // LCC1: Radius of no compensation area (matches default)
    {0x87, 0x1b},  // LCC2: X coordinate offset (default: 0x00 -> 0x1B = +27 pixels)
    {0x88, 0xaf},  // LCC3: Y coordinate offset (default: 0x00 -> 0xAF = +175 pixels)
    {0x89, 0x21},  // LCC4: R channel compensation (default: 0x00 -> 0x21)
    {0x8a, 0x20},  // LCC5: G channel compensation (default: 0x00 -> 0x20)
    {0x8b, 0x20},  // LCC6: B channel compensation (default: 0x00 -> 0x20)

    // ========================================
    // COLOR MATRIX (RGB to YUV conversion)
    // ========================================
    {0xbb, 0xac},  // REGBB: Color matrix coefficient 1 (default: 0x2C -> 0xAC)
    {0xbc, 0xae},  // REGBC: Color matrix coefficient 2 (default: 0x24 -> 0xAE)
    {0xbd, 0x02},  // REGBD: Color matrix coefficient 3 (default: 0x08 -> 0x02)
    {0xbe, 0x1f},  // REGBE: Color matrix coefficient 4 (default: 0x14 -> 0x1F)
    {0xbf, 0x93},  // REGBF: Color matrix coefficient 5 (default: 0x24 -> 0x93)
    {0xc0, 0xb1},  // REGC0: Color matrix coefficient 6 (default: 0x38 -> 0xB1)
    {0xc1, 0x1a},  // REGC1: Color matrix control (default: 0x1E -> 0x1A)
                   // Custom color matrix for specific color reproduction

    // ========================================
    // EDGE ENHANCEMENT & DENOISE
    // ========================================
    {0xb4, 0x06},  // REGB4: Edge and denoise control (matches default)
    {0xb7, 0x06},  // REGB7: OFFSET (default: 0x10 -> 0x06, reduces offset)
    {0xb8, 0x04},  // REGB8: BASE1 (default: 0x1E -> 0x04, lower threshold)
    {0xb9, 0x00},  // REGB9: BASE2 (default: 0x02 -> 0x00, minimum threshold)
    {0xba, 0x04},  // REGBA: Gain selection and denoise control
                   // Default: 0x09 -> 0x04

    // ========================================
    // AEC/AGC TARGET LEVELS
    // ========================================
    {0x24, 0x80},  // WPT: AEC/AGC upper limit (default: 0x78 -> 0x80, +8 higher target)
    {0x25, 0x70},  // BPT: AEC/AGC lower limit (default: 0x68 -> 0x70, +8 higher target)
    {0x26, 0xa2},  // VPT: Fast mode operating region (default: 0xD4 -> 0xA2)
                   // Narrower fast mode window for more stable exposure


    // ========================================
    // UV ADJUSTMENT
    // ========================================
    /*{0x5a, 0x10},  // UV_CTR0: Slope of UV curve (default: 0x01 -> 0x10)
    {0x5b, 0xa1},  // UV_CTR1: UV gain threshold and Y intercept
                   // Default: 0xFF -> 0xA1
    {0x5c, 0x3a},  // UV_CTR2: UV gain threshold MSBs and manual UV
                   // Default: 0x1F -> 0x3A
    {0x5d, 0x20},  // UV_CTR3: UV gain low threshold (default: 0x00 -> 0x20)
                   // Reduces chrominance in low light conditions
    */
    // ========================================
    // GAMMA CURVE CONFIGURATION
    // ========================================
    // Custom gamma curve for better dynamic range
    {0xa3, 0x04},  // GAM1:  Segment 1 (default: 0x10 -> 0x04, darker shadows)
    {0xa4, 0x0c},  // GAM2:  Segment 2 (default: 0x12 -> 0x0C, darker shadows)
    {0xa5, 0x23},  // GAM3:  Segment 3 (default: 0x35 -> 0x23, darker)
    {0xa6, 0x55},  // GAM4:  Segment 4 (default: 0x5A -> 0x55, slightly darker)
    {0xa7, 0x69},  // GAM5:  Segment 5 (matches default)
    {0xa8, 0x78},  // GAM6:  Segment 6 (default: 0x76 -> 0x78, slightly brighter)
    {0xa9, 0x80},  // GAM7:  Segment 7 (matches default)
    {0xaa, 0x88},  // GAM8:  Segment 8 (matches default)
    {0xab, 0x90},  // GAM9:  Segment 9 (default: 0x8F -> 0x90, slightly brighter)
    {0xac, 0x97},  // GAM10: Segment 10 (default: 0x96 -> 0x97, slightly brighter)
    {0xad, 0xa4},  // GAM11: Segment 11 (default: 0xA3 -> 0xA4, slightly brighter)
    {0xae, 0xb0},  // GAM12: Segment 12 (default: 0xAF -> 0xB0, slightly brighter)
    {0xaf, 0xc5},  // GAM13: Segment 13 (default: 0xC4 -> 0xC5, slightly brighter)
    {0xb0, 0xd7},  // GAM14: Segment 14 (matches default)
    {0xb1, 0xe8},  // GAM15: Segment 15 (matches default)
    {0xb2, 0x20},  // SLOPE: Gamma curve highest segment slope (matches default)
                   // Custom gamma curve: darker shadows, slightly brighter midtones/highlights

    // ========================================
    // AUTO WHITE BALANCE (AWB) CONTROL
    // ========================================
    // AWB control registers 0x8C-0xA2 (23 registers)
    // These configure color temperature detection and correction
    {0x8c, 0x5e}, {0x8d, 0x11}, {0x8e, 0x12}, {0x8f, 0x19},
    {0x90, 0x50}, {0x91, 0x20}, {0x92, 0x99}, {0x93, 0x8b},
    {0x94, 0x13}, {0x95, 0x14}, {0x96, 0xf0}, {0x97, 0x10},
    {0x98, 0x34}, {0x99, 0x32}, {0x9a, 0x53}, {0x9b, 0x41},
    {0x9c, 0xf0}, {0x9d, 0xf0}, {0x9e, 0xf0}, {0x9f, 0xff},
    {0xa0, 0x66}, {0xa1, 0x52}, {0xa2, 0x11},

    // ========================================
    // AGC & BANDING CONFIGURATION
    // ========================================
    {0x14, 0x41},  // REG14: AGC ceiling and banding
                   // Default: 0x30
                   // Bit[6:4]: AGC ceiling = 2× to 128x 
                   // Bit[0]=1: 50 Hz banding (default was 0=60Hz)
                   // Lower AGC ceiling reduces noise in low light

    // ========================================
    // SATURATION CONTROL (SDE)
    // ========================================
    {0xd8, 0x50},  // REGD8: SAT_U (default: 0x40 -> 0x50, +25% U saturation)
    {0xd9, 0x50},  // REGD9: SAT_V (default: 0x40 -> 0x50, +25% V saturation)
                   // Increases color saturation for more vivid colors

    {0xd2, 0x12},  // REGD2: SDE_CTRL - Special Digital Effects control
                   // Default: 0x00 -> 0x02
                   // Bit[5]=0: GRAY_EN disabled
                   // Bit[1]=1: SAT_EN (saturation control enabled)

    // ========================================
    // BANDING FILTER (50Hz/60Hz)
    // ========================================
    {0x50, 0x6e},  // BD50st: 50 Hz banding AEC (default: 0x9A -> 0x6E)
    {0x51, 0x5c},  // BD60ST: 60 Hz banding AEC (default: 0x80 -> 0x5C)

    // ========================================
    // AEC/AGC/AWB ENABLE
    // ========================================
    {0x13, 0xf7},  // REG13: Auto control enables
                   // Default: 0xE5 -> 0xF7
                   // Bit[7]=1: Fast AGC/AEC algorithm enabled
                   // Bit[6]=1: AEC step size unlimited
                   // Bit[5]=1: Banding filter ON
                   // Bit[4]=1: AEC below banding enabled
                   // Bit[3]=0: Sub-line exposure disabled (changed)
                   // Bit[2]=1: AGC auto control enabled
                   // Bit[1]=1: AWB auto control enabled
                   // Bit[0]=1: Exposure auto control enabled

    // ========================================
    // CLOCK & PLL RECONFIGURATION
    // ========================================
    {0x11, 0x00},  // CLKRC: Clock control (reconfirm no division)

    {0x29, 0x50},  // PLL: PLL configuration
                   // Default: 0xA2 -> 0x50
                   // Bit[7:6]=01: PLL divider = /2
                   // Bit[5:4]=01: PLL output = 4× (default was also 4×)
                   // Bit[3]=0: PLL not reset
                   // Adjusted for 24MHz input clock

    {0x15, 0x00},  // REG15: Reset auto frame rate and digital gain
                   // Back to default (disables features set earlier)
                   // Bit[7]=0: Auto frame rate control disabled
                   // Bit[1:0]=00: No digital gain

    // ========================================
    // BLANKING & TIMING ADJUSTMENTS
    // ========================================
    {0x2a, 0x30},  // EXHCL: Dummy pixel control

    {0x2b, 0x00},  // EXHCH: Horizontal delay/porch
                   // Default: 0x0B -> 0x00
                   // Removes horizontal dummy pixels

    {0x2c, 0x00},  // DM_LN: Dummy line LSBs

    {0x2d, 0x20},  // ADVFL: Vertical frame delay LSBs
                   // Default: 0x00 -> 0x20 (32 dummy lines)
                   // Adds delay between frames (inter-frame blanking)

    {0x2e, 0x00},  // ADVFH: Vertical frame delay MSBs (matches default)

    // ========================================
    // LENS CORRECTION (FINAL ADJUSTMENT)
    // ========================================
    /*{0x85, 0x00},  // LCC0: Lens correction control
                   // Default: 0x00 -> 0x90
                   // Bit[7]=1: LENC enabled (was disabled earlier)
                   // Bit[4]=1: LENC gain enabled

    {0x86, 0x18},  // LCC1: Radius (default: 0x00 -> 0x18 = 24 pixels)
    {0x87, 0xb0},  // LCC2: X coordinate (default: 0x00 -> 0xB0 = +176 pixels)
    {0x88, 0xa0},  // LCC3: Y coordinate (default: 0x00 -> 0xA0 = +160 pixels)
    {0x89, 0x24},  // LCC4: R channel (default: 0x00 -> 0x24)
    {0x8a, 0x1f},  // LCC5: G channel (default: 0x00 -> 0x1F)
    {0x8b, 0x21},  // LCC6: B channel (default: 0x00 -> 0x21)*/

    // ========================================
    // OUTPUT TIMING CONTROL
    // ========================================
    {0x28, 0x02},  // REG28: Output signal timing
                   // Default: 0x00 -> 0x02
                   // Bit[2]=0: VSYNC on falling edge of PCLK (default)
                   // Bit[1]=1: VSYNC negative polarity

    // ========================================
    // FINAL OUTPUT CONFIGURATION
    // ========================================
    {0x0c, 0x16},  // REG0C: Image orientation final setting
                   // Changed from earlier 0xD6 -> 0x56
                   // Bit[7]=0: Vertical flip disabled (CHANGED)
                   // Bit[6]=1: Horizontal mirror enabled
                   // Bit[4]=1: YU/YV swap
                   // Bit[2]=1: Clock output pin active
                   // Bit[1]=1: VSYNC/HREF/PCLK output state

    {0xda, 0x80},  // REGDA: UREG - U fixed value (matches default)
    {0xdb, 0x80},  // REGDB: VREG - V fixed value (matches default)
    
    {0xff, 0xff},  // END MARKER (not a valid register)

};
