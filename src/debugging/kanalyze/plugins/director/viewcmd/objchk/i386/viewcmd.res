L xUfeò  	      .debug$S        I                  @ B.rsrc$01            Ö   v         @  @.rsrc$02        h                @  @    	     objchk\i386\viewcmd.res#    Microsoft CVTRES 5.00.2134.1                         8                    P                    h                 	                    	         @              $                        $4   V S _ V E R S I O N _ I N F O     ½ïþ               ?                           S t r i n g F i l e I n f o   ^   0 4 0 9 0 4 b 0   4 
  C o m p a n y N a m e     M i c r o s o f t    1  F i l e D e s c r i p t i o n     V I E W C M D   P l u g - I n   f o r   K e r n e l   M e m o r y   S p a c e   A n a l y z e r     6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     8   I n t e r n a l N a m e   v i e w c m d . d l l   P   L e g a l C o p y r i g h t   C o p y r i g h t   ©   1 9 9 1 - 1 9 9 9   @   O r i g i n a l F i l e n a m e   v i e w c m d . d l l   J   P r o d u c t N a m e     M i c r o s o f t   W i n d o w s   N T     :   P r o d u c t V e r s i o n   1 ,   0 ,   0 ,   1     D    V a r F i l e I n f o     $    T r a n s l a t i o n     	°                8   Failed to enumerate stored item "%1" (err=%2!u!).
 @   Could not get item description of ID:%1!05x! (err=%2!u!).
 @   Could not allocate memory in %1, size=%2!u! (err=%3!u!).
  4   Failed to enumerate type "%1" (err=%2!u!).
    D   Could not get type information of Handle:%1!08x! (err=%2!u!).
 @   Could not get item information of ID:%1!05x! (err=%2!u!).
 D   Failed to enumerate linked item with ID:%1!05x! (err=%2!u!).
      %1 failed (err=%2!u!).
    4   Failed in CommandLineToArgvW, %1 (err=%2!u!).
     Handle   Type Name                                          Support Plug-in
---------------------------------------------------------------------------
      %1!08x! %2!-50s! %3!-s!
       Allowed container types
   d   Reported Item
---------------------------------------------------------------------------
    4   @%1!08x!:%2!05x! (ID:%3!05x!) %4!-30s! by %5
     
  h   Description of Type
---------------------------------------------------------------------------
  T   ---------------------------------------------------------------------------
   0   %1 @%2!08x! (ID:%3!05x!, Reported by %4)
  0   %1 @%2!08x! (ID:%3!05x!, Linked by %4)
      
type [type_name] [-h type_handle]
   - display registered types.

     type_name   Specify type name string. You can use '*(asterisk)' as a wild
                 card at the end of string. If you use a wild card, every
                 matched type information is enumerated in short form. If full
                 type_name is specified, display type information in detail.
     -h          Specify a hexadecimal type handle.

find [type_name] [start_addr [end_addr] [-o]] [-v]
   - find located item by type_name or  memory range.

     type_name   Specify type name string. You can use '*(asterisk)' as a wild
                 card at the end of string.
     start_addr  Hexadecimal start address of memory range. Default is 0. If
                 you omit both start_addr and end_addr, memory range becomes
                 whole virtual address.
     end_addr    Hexadecimal end address of memory range. If you specify
                 start_addr only, end_addr becomes the same as start_addr.
     -o          Display all items that overlap with specified memory range.
     -v          Display formatted description of each item.

view item_id
   - display item information and formatted description.

     item_id     Hexadecimal value of item ID.

link item_id [depth] [-{b|f|m}]
   - display linked items.

     item_id     Hexadecimal value of item ID.
     depth       Specify nesting level of link. Default nesting level is 1.
     -b          Display items from which an item links.
     -f          Display items to which an item links.
     -m          Display items with which an item links (forward and backward).

d{b|d} [address] [length]
   - hexadecimal dump of given range.

     address     Hexadecimal start address of memory range.
     length      Hexadecimal length of memory range.

help, ?
   - show this help.

exit
   - exit from command mode.
   @comp.idV ÿÿ   .debug$S       I                 .rsrc$01                        .rsrc$02       h                $R000000        $R000328(          