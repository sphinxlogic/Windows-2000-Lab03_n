L �Ufe�  
      .debug$S        I   �               @ B.rsrc$01        �   �   �         @  @.rsrc$02        �  �              @  @    	     objchk\i386\wmarkps.res#    Microsoft CVTRES 5.00.2134.1                      �SP  8  �                  X  �                  p  �   �  �               	  �                      �                      �       �                             '           �       �       �   	    userdict /DrawWaterMark get exec

 
 userdict /DrawWaterMark {
userdict begin
/Watermark (%1!S!) def
/FontSize %2!d! def
/Font /Helvetica def
/WaterMarkColor {%3 setrgbcolor} bind def
/Angle %4 def

gsave
initgraphics

Angle rotate

clippath
pathbbox /MaxY exch def /MaxX exch def /MinY exch def /MinX exch def

Font findfont FontSize scalefont setfont
/MarkLen Watermark stringwidth pop 1.20 mul def
WaterMarkColor

MinY FontSize MaxY
{
  MinX MarkLen MaxX
  {
    1 index moveto Watermark show
  } for
  pop
} bind for
grestore
end
} bind put

 
�4   V S _ V E R S I O N _ I N F O     ���               ?                          S t r i n g F i l e I n f o   �   0 4 0 9 0 4 b 0   j )  C o m m e n t s   W r i t t e n   b y   N T   I m a g i n g   S e r v i c e s   T e s t   T e a m     @   C o m p a n y N a m e     M i c r o s o f t   C o r p .   p $  F i l e D e s c r i p t i o n     O E M   C u s t o m i z a t i o n   W a t e r   M a r k   S a m p l e   6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     0   I n t e r n a l N a m e   W M a r k P S   F   L e g a l C o p y r i g h t   C o p y r i g h t   �   1 9 9 8     s  L e g a l T r a d e m a r k s     M i c r o s o f t �   i s   a   r e g i s t e r e d   t r a d e m a r k   o f   M i c r o s o f t   C o r p o r a t i o n .   W i n d o w s ( T M )   i s   a   t r a d e m a r k   o f   M i c r o s o f t   C o r p o r a t i o n     @   O r i g i n a l F i l e n a m e   W M a r k P S . D L L        P r i v a t e B u i l d   H   P r o d u c t N a m e     M i c r o s o f t   W a t e r M a r k   ,   P r o d u c t V e r s i o n   1 . 0        S p e c i a l B u i l d   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	�    @comp.idV ��   .debug$S       I                 .rsrc$01       �                .rsrc$02       �                $R000000        $R000028(       $R000248H          