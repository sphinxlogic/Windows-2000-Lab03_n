/*-----------------------------------------------------------------------
|   stdpal.h
|
|   Standard App Palette useful for OLE applications.  v 1.01
|
|   #include this file in the same file as HpalCreateAppPalette
|
|   NOTE:  Palette MUST be created with HpalCreateAppPalette
|
|   Copyright 1992 - 1998 Microsoft Corporation. All rights reserved.
|
-----------------------------------------------------------------------*/


unsigned char palSVGA[256][3] =
        {
        // R     G     B
        {0x00, 0x00, 0x00}, // 0 Sys Black  gray 0
        {0x80, 0x00, 0x00}, // 1 Sys Dk Red
        {0x00, 0x80, 0x00}, // 2 Sys Dk Green
        {0x80, 0x80, 0x00}, // 3 Sys Dk Yellow
        {0x00, 0x00, 0x80}, // 4 Sys Dk Blue
        {0x80, 0x00, 0x80}, // 5 Sys Dk Violet
        {0x00, 0x80, 0x80}, // 6 Sys Dk Cyan
        {0xc0, 0xc0, 0xc0}, // 7 Sys Lt Grey    gray 192
        {0xc0, 0xdc, 0xc0}, // 8 Sys 8
        {0xa6, 0xca, 0xf0}, // 9 Sys 9 (the first 10 are fixed by Windows)

        {0x80, 0x00, 0x00}, // 10 Sys Dk Red repeat
        {0x00, 0x80, 0x00}, // 11 Sys Dk Green repeat
        {0x80, 0x80, 0x00}, // 12 Sys Dk Yellow repeat
        {0x00, 0x00, 0x80}, // 13 Sys Dk Blue repeat
        {0x80, 0x00, 0x80}, // 14 Sys Dk Violet repeat
        {0x00, 0x80, 0x80}, // 15 Sys Dk Cyan repeat
        {0x80, 0x80, 0x80}, // 16 Sys Dk Grey repeat    gray 128
        {0x80, 0x80, 0xff}, // 17 Excel Chart Fill 1
        {0x80, 0x20, 0x60}, // 18 Excel Chart Fill 2
        {0xff, 0xff, 0xc0}, // 19 Excel Chart Fill 3
        {0xa0, 0xe0, 0xe0}, // 20 Excel Chart Fill 4
        {0x60, 0x00, 0x80}, // 21 Excel Chart Fill 4
        {0xff, 0x80, 0x80}, // 22 Excel Chart Fill 6
        {0x00, 0x80, 0xc0}, // 23 Excel Chart Fill 7
        {0xc0, 0xc0, 0xff}, // 24 Excel Chart Fill 8
        {0x00, 0xcf, 0xff}, // 25 Excel clrt entry
        {0x69, 0xff, 0xff}, // 26 Excel clrt entry
        {0xe0, 0xff, 0xe0}, // 27 Excel clrt entry
        {0xdd, 0x9c, 0xb3}, // 28 Excel clrt entry
        {0xb3, 0x8f, 0xee}, // 29 Excel clrt entry
        {0x2a, 0x6f, 0xf9}, // 30 Excel clrt entry
        {0x3f, 0xb8, 0xcd}, // 31 Excel clrt entry
        {0x48, 0x84, 0x36}, // 32 Excel clrt entry
        {0x95, 0x8c, 0x41}, // 33 Excel clrt entry
        {0x8e, 0x5e, 0x42}, // 34 Excel clrt entry
        {0xa0, 0x62, 0x7a}, // 35 Excel clrt entry
        {0x62, 0x4f, 0xac}, // 36 Excel clrt entry
        {0x1d, 0x2f, 0xbe}, // 37 Excel clrt entry
        {0x28, 0x66, 0x76}, // 38 Excel clrt entry
        {0x00, 0x45, 0x00}, // 39 Excel clrt entry
        {0x45, 0x3e, 0x01}, // 40 Excel clrt entry
        {0x6a, 0x28, 0x13}, // 41 Excel clrt entry
        {0x85, 0x39, 0x6a}, // 42 Excel clrt entry
        {0x4a, 0x32, 0x85}, // 43 Excel clrt entry
        {0x04, 0x04, 0x04}, // 44   gray 4
        {0x08, 0x08, 0x08}, // 45   gray 8
        {0x0c, 0x0c, 0x0c}, // 46   gray 12
        {0x11, 0x11, 0x11}, // 47   gray 17
        {0x16, 0x16, 0x16}, // 48   gray 22
        {0x1c, 0x1c, 0x1c}, // 49   gray 28
        {0x22, 0x22, 0x22}, // 50   gray 34
        {0x29, 0x29, 0x29}, // 51   gray 41
        {0x30, 0x30, 0x30}, // 52   gray 48
        {0x5f, 0x5f, 0x5f}, // 53 swapped so inversions look good   gray 95
        {0x55, 0x55, 0x55}, // 54 swapped so inversions look good   gray 85
        {0x4d, 0x4d, 0x4d}, // 55 swapped so inversions look good   gray 77
        {0x42, 0x42, 0x42}, // 56 swapped so inversions look good   gray 66
        {0x39, 0x39, 0x39}, // 57 swapped so inversions look good   gray 57
        {0x00, 0x07, 0x00}, // 58
        {0x0d, 0x00, 0x00}, // 59
        {0xb7, 0x99, 0x81}, // 60
        {0x84, 0x99, 0xb4}, // 61
        {0xbd, 0xbd, 0x90}, // 62
        {0x7f, 0x7f, 0x60}, // 63
        {0x60, 0x60, 0x7f}, // 64
        {0x00, 0x0e, 0x00}, // 65
        {0x1b, 0x00, 0x00}, // 66
        {0x28, 0x00, 0x00}, // 67
        {0x08, 0x09, 0x2b}, // 68
        {0x00, 0x1d, 0x00}, // 69
        {0x39, 0x00, 0x00}, // 70
        {0x00, 0x00, 0x9b}, // 71
        {0x00, 0x25, 0x00}, // 72
        {0x49, 0x00, 0x00}, // 73
        {0x11, 0x11, 0x3b}, // 74
        {0x00, 0x2f, 0x00}, // 75
        {0x5d, 0x00, 0x00}, // 76
        {0x17, 0x17, 0x45}, // 77
        {0x00, 0x3a, 0x00}, // 78
        {0x49, 0x11, 0x11}, // 79
        {0x1c, 0x1c, 0x53}, // 80
        {0x00, 0x16, 0xff}, // 81
        {0x2b, 0x00, 0xff}, // 82
        {0x21, 0x21, 0x6c}, // 83
        {0x59, 0x14, 0x14}, // 84
        {0x00, 0x51, 0x00}, // 85
        {0x47, 0x1a, 0x6a}, // 86
        {0x19, 0x32, 0x67}, // 87
        {0x00, 0x61, 0x00}, // 88
        {0x00, 0x31, 0xff}, // 89
        {0x61, 0x00, 0xff}, // 90
        {0x53, 0x20, 0x7b}, // 91
        {0x16, 0x43, 0x67}, // 92
        {0x2e, 0x2e, 0xe2}, // 93
        {0x26, 0x59, 0x16}, // 94
        {0x51, 0x46, 0x04}, // 95
        {0x68, 0x2e, 0x49}, // 96
        {0x07, 0x52, 0x8f}, // 97
        {0x6a, 0x18, 0xb8}, // 98
        {0x90, 0x23, 0x15}, // 99
        {0x00, 0x53, 0xff}, // 100
        {0xa3, 0x00, 0xff}, // 101
        {0x6a, 0x4a, 0x12}, // 102
        {0x75, 0x33, 0x6c}, // 103
        {0x4a, 0x41, 0x9a}, // 104
        {0x37, 0x65, 0x0b}, // 105
        {0xa4, 0x2c, 0x15}, // 106
        {0x83, 0x1f, 0xb1}, // 107
        {0x4e, 0x2c, 0xff}, // 108
        {0x20, 0x51, 0xb6}, // 109
        {0x08, 0x64, 0x92}, // 110
        {0x6f, 0x56, 0x0b}, // 111
        {0x59, 0x43, 0xad}, // 112
        {0x36, 0x72, 0x12}, // 113
        {0xb0, 0x33, 0x17}, // 114
        {0x00, 0xa1, 0x00}, // 115
        {0x77, 0x5f, 0x1f}, // 116
        {0x89, 0x47, 0x71}, // 117
        {0xb0, 0x43, 0x1c}, // 118
        {0xb7, 0x2d, 0x7d}, // 119
        {0x00, 0x86, 0x95}, // 120
        {0x7a, 0x6e, 0x23}, // 121
        {0x26, 0x9f, 0x00}, // 122
        {0x73, 0xa9, 0x01}, // 123
        {0x00, 0x00, 0x00}, // 124 free 0   gray 0
        {0x00, 0x00, 0x00}, // 125 free 2   gray 0
        {0x00, 0x00, 0x00}, // 126 free 4   gray 0
        {0x00, 0x00, 0x00}, // 127 free 6   gray 0
        {0x00, 0x00, 0x00}, // 128 free 7   gray 0
        {0x00, 0x00, 0x00}, // 129 free 5   gray 0
        {0x00, 0x00, 0x00}, // 130 free 3   gray 0
        {0x00, 0x00, 0x00}, // 131 free 1   gray 0
        {0x00, 0xca, 0x00}, // 132
        {0xac, 0x5b, 0x01}, // 133
        {0x20, 0x1d, 0xc2}, // 134
        {0x94, 0x52, 0x70}, // 135
        {0x24, 0xaa, 0x4c}, // 136
        {0x0a, 0x94, 0x89}, // 137
        {0x36, 0x6e, 0x7b}, // 138
        {0x44, 0x75, 0x90}, // 139
        {0xff, 0x00, 0xa8}, // 140
        {0x00, 0x71, 0xff}, // 141
        {0xdf, 0x00, 0xff}, // 142
        {0x56, 0x91, 0x4a}, // 143
        {0x34, 0x48, 0xf8}, // 144
        {0xcc, 0x32, 0x82}, // 145
        {0xe4, 0x41, 0x70}, // 146
        {0x68, 0xca, 0x01}, // 147
        {0x36, 0xbc, 0x42}, // 148
        {0x00, 0x9a, 0xff}, // 149
        {0x96, 0x22, 0xb7}, // 150
        {0x85, 0x7d, 0x33}, // 151
        {0x25, 0xb7, 0x8c}, // 152
        {0x36, 0x5a, 0xed}, // 153
        {0x5c, 0xff, 0x00}, // 154
        {0xff, 0x48, 0x00}, // 155
        {0x22, 0x9b, 0xa2}, // 156
        {0x42, 0xcf, 0x4d}, // 157
        {0xc2, 0x58, 0x52}, // 158
        {0x20, 0xd3, 0x95}, // 159
        {0xa5, 0x24, 0xe0}, // 160
        {0x73, 0x56, 0xb5}, // 161
        {0xa9, 0xa9, 0x00}, // 162
        {0xd0, 0x6f, 0x3c}, // 163
        {0x67, 0x9f, 0x58}, // 164
        {0x89, 0xcf, 0x0b}, // 165
        {0xff, 0xac, 0x00}, // 166
        {0xa7, 0x2e, 0xfe}, // 167
        {0xe2, 0x59, 0x7f}, // 168
        {0x4c, 0xdc, 0x67}, // 169
        {0xff, 0x18, 0xff}, // 170
        {0x3a, 0x7d, 0xff}, // 171
        {0xb1, 0xd0, 0x18}, // 172
        {0xc7, 0xff, 0x00}, // 173
        {0xff, 0xe2, 0x00}, // 174
        {0xdf, 0x9a, 0x3d}, // 175
        {0x56, 0x81, 0x9f}, // 176
        {0xc6, 0x43, 0xba}, // 177
        {0xaf, 0x71, 0x8b}, // 178
        {0x38, 0xa2, 0xc9}, // 179
        {0xd1, 0x53, 0xce}, // 180
        {0xff, 0x9a, 0x65}, // 181
        {0x46, 0xca, 0xdb}, // 182
        {0xff, 0x4d, 0xff}, // 183
        {0xc8, 0xe9, 0x6a}, // 184
        {0x4c, 0xde, 0xe0}, // 185
        {0xff, 0x98, 0xff}, // 186
        {0xdf, 0xc0, 0x82}, // 187
        {0xe9, 0xec, 0xa5}, // 188
        {0xf5, 0xf6, 0xcd}, // 189
        {0xff, 0xd0, 0xff}, // 190
        {0xb1, 0xac, 0x5a}, // 191
        {0x63, 0x91, 0xae}, // 192
        {0x22, 0x4c, 0x65}, // 193
        {0x8d, 0x4e, 0x3f}, // 194
        {0x50, 0x70, 0x70}, // 195
        {0xd0, 0xff, 0xff}, // 196
        {0xff, 0xe7, 0xff}, // 197
        {0x69, 0x69, 0x69}, // 198  gray 105
        {0x77, 0x77, 0x77}, // 199  gray 119
        {0x86, 0x86, 0x86}, // 200  gray 134
        {0x96, 0x96, 0x96}, // 201  gray 150
        {0x9d, 0x9d, 0x9d}, // 202  gray 157
        {0xa4, 0xa4, 0xa4}, // 203  gray 164
        {0xb2, 0xb2, 0xb2}, // 204  gray 178
        {0xcb, 0xcb, 0xcb}, // 205  gray 203
        {0xd7, 0xd7, 0xd7}, // 206  gray 215
        {0xdd, 0xdd, 0xdd}, // 207  gray 221
        {0xe3, 0xe3, 0xe3}, // 208  gray 227
        {0xea, 0xea, 0xea}, // 209  gray 234
        {0xf1, 0xf1, 0xf1}, // 210  gray 241
        {0xf8, 0xf8, 0xf8}, // 211  gray 248
        {0xb2, 0xc1, 0x66}, // 212
        {0x80, 0xbf, 0x78}, // 213
        {0xc6, 0xf0, 0xf0}, // 214
        {0xb2, 0xa4, 0xff}, // 215
        {0xff, 0xb3, 0xff}, // 216
        {0xd1, 0x8e, 0xa3}, // 217
        {0xc3, 0xdc, 0x37}, // 218
        {0xa0, 0x9e, 0x54}, // 219
        {0x76, 0xae, 0x70}, // 220
        {0x78, 0x9e, 0xc1}, // 221
        {0x83, 0x64, 0xbf}, // 222
        {0xa4, 0x83, 0xd3}, // 223
        {0xd1, 0x3f, 0x32}, // 224
        {0xff, 0x7d, 0x00}, // 225
        {0x44, 0x78, 0x23}, // 226
        {0x24, 0x5f, 0x60}, // 227
        {0x0e, 0x0e, 0x2c}, // 228
        {0xbe, 0x00, 0x00}, // 229
        {0xff, 0x1f, 0x00}, // 230
        {0x31, 0x39, 0x00}, // 231
        {0xd9, 0x85, 0x3e}, // 232
        {0x02, 0x77, 0x85}, // 233
        {0xb0, 0xd8, 0x81}, // 234
        {0x56, 0x21, 0x1d}, // 235
        {0x00, 0x00, 0x30}, // 236
        {0x88, 0xc8, 0xb3}, // 237
        {0xa0, 0x79, 0x00}, // 238
        {0xc0, 0xc0, 0xc0}, // 239 Sys Dk Grey repeat inversion gray 192
        {0xea, 0x70, 0x81}, // 240
        {0x51, 0xf1, 0x69}, // 241
        {0xff, 0xff, 0x80}, // 242
        {0x91, 0x74, 0xcd}, // 243
        {0xff, 0x7c, 0xff}, // 244
        {0xa2, 0xff, 0xff}, // 245

        {0xff, 0xfb, 0xf0}, // 246 Sys Reserved
        {0xa0, 0xa0, 0xa4}, // 247 Sys Reserved
        {0x80, 0x80, 0x80}, // 248 Sys Lt Gray  gray 128
        {0xff, 0x00, 0x00}, // 249 Sys Red
        {0x00, 0xff, 0x00}, // 250 Sys Green
        {0xff, 0xff, 0x00}, // 251 Sys Yellow
        {0x00, 0x00, 0xff}, // 252 Sys Blue
        {0xff, 0x00, 0xff}, // 253 Sys Violet
        {0x00, 0xff, 0xff}, // 254 Sys Cyan
        {0xff, 0xff, 0xff} // 255 Sys White gray 255
        };