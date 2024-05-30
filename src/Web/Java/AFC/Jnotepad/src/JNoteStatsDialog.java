//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

/**
*	JNoteStatsDialog
*
*	Displays file statistics/properties in a dialog box. Displays line,
*	word, character, and character with spaces count. 
*
*	@version	1.0, 8/3/97
*/

import com.ms.ui.*;
import java.util.StringTokenizer;

public class JNoteStatsDialog extends JNoteDialog implements IConstants
{
	private UIDrawText wordsField;						// field which holds the word count
	private UIDrawText linesField;						// field which holds the line count
	private UIDrawText charsField;						// field which holds the character count
	private UIDrawText charsWithSpacesField;			// field which holds the characters with spaces count
	private UIGroup fileBox;							// group box which contains the file's name
	private IFileOperationTargetExt  fileControl;			// file control we are performing statistics on.
	
	public JNoteStatsDialog(UIFrame parentframe, IFileOperationTargetExt  filecontrol)
	{
		super(parentframe, "File Statistics", true);
		
		init(filecontrol);
	}
	
	private void init(IFileOperationTargetExt  filecontrol)
	{
		fileControl = filecontrol;
		loadDialog(JNotePad.getResources(), IDR_FILESTATS_DIALOG);
		
		linesField = (UIDrawText)getComponentFromID(IDR_FILESTATS_LINES);
		wordsField = (UIDrawText)getComponentFromID(IDR_FILESTATS_WORDS);
		charsField = (UIDrawText)getComponentFromID(IDR_FILESTATS_CHARS);
		charsWithSpacesField = (UIDrawText)getComponentFromID(IDR_FILESTATS_CHARS_W_SPACES);
								
		fileBox = (UIGroup)getComponentFromID(IDR_FILESTATS_FILEBOX);			
		fileBox.setName(fileControl.getDisplayFileName());			
		
		invalidateAll();			
	}
	
	
	public void initDialog()
	{								
		fileBox = (UIGroup)getComponentFromID(IDR_FILESTATS_FILEBOX);			
		fileBox.setName(fileControl.getDisplayFileName());						
		
		String text = fileControl.getText();
		int iTextLen = text.length();
		
		int iWords = 0;
		int iLines = 0;
		int iChars = 0;
		int iSpaces = 0;
		
		int iIndex = 0;
		char ch;
		
		//
		// Words require some non-white space to be between thenm
		//
		boolean bNonWhiteSpace=false;
		while (iIndex < iTextLen)
		{
			ch = text.charAt(iIndex);
			
			if (ch == '\n')
			{
				if(bNonWhiteSpace)
					iWords++;
				iLines++;
				bNonWhiteSpace=false;
			}
			else if (Character.isSpace(ch) && (ch != '\r'))
			{
				iWords++;
				iSpaces++;
			}
			else
			{
				iChars++;
				bNonWhiteSpace=true;
			}
			
			if (".;,".indexOf(ch) > -1)
			{
				iWords++;
				bNonWhiteSpace=false;
			}
			
			iIndex++;					
		}

		if(bNonWhiteSpace)
			iWords++;

		wordsField.setValueText(String.valueOf(iWords));
		linesField.setValueText(String.valueOf(iLines));
		charsField.setValueText(String.valueOf(iChars));
		charsWithSpacesField.setValueText(String.valueOf(iChars+iSpaces));			

		getComponentFromID(IDR_FILESTATS_OK).requestFocus();
	}
	
}
