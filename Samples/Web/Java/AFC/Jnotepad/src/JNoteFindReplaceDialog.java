//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import java.awt.*;

/**
*	Adds find and replace algorithms to UIFindReplaceDialog as well as
*	support for using ITextOperationTargetExt interfaces.
*
*	@version	1.0, 8/1/97
*/

public class JNoteFindReplaceDialog extends UIFindReplaceDialog
{
	/**
	*	Edit control we're doing find and replace in
	*/
	protected ITextOperationTargetExt textTarget;
	
	/**
	*	The parent frame window
	*/
	protected UIFrame parentFrame;
	
	/**
	*	Current search position
	*/
	private int iCurrentSearchPos;
	
	/**
	*	Number of hits found so far.
	*/
	private int iNumHits;
	
	/**
	*	Identifier specifying no search is active.	
	*/
	private static final int NO_CURRENT_SEARCH = -2;
	
	/**
	*	Creates a JNoteFindReplaceDialog
	*
	*	@param	frame	Parent frame
	*	@param	title	Title of the dialog
	*	@param	modal	true if the dialog is to be modal, false if it is to be modeless.
	*	@param	target	The ITextOperationTargetExt object which will be searched.
	*/
	JNoteFindReplaceDialog(UIFrame frame, String title, boolean modal, ITextOperationTargetExt target)
	{
		super(frame, title, modal);
		textTarget = target;
		parentFrame = frame;
		// init variables for starting a new search
		startNewSearch();			
	}
	
	/**
	*	Overrides UIFindReplaceDialog.doFindNext(). Calls search() to do searching,
	*	and highlights the found word. If no more words are left to find, displays a 
	*	dialog box informing the user of this.
	*
	*	@returns	true if a word was found, false if not.
	*/
	public boolean doFindNext()
	{
		// find the index of the next search hit
		int iHitStart = search();
		
		// if the word is found
		if (iHitStart > -1)
		{
			// hilight the word
			int iFindTextLen = getFindText().length();
			textTarget.setSelection(iHitStart, iHitStart+iFindTextLen);
			textTarget.moveTheCaret(iHitStart+iFindTextLen);
			return true;
		}
		
		UIMessageBox msgbox = null;
		if (iNumHits > 0)
		{
			// if no more words found, splash up a message box and reset the search position
			// we've finished searching
			msgbox = new UIMessageBox(parentFrame, 
				JNotePad.loadString(ResourceIDs.IDS_MSGFINDTEXT),
				JNotePad.loadString(ResourceIDs.IDS_MSGSEARCHDONE),
				UIMessageBox.INFORMATION, UIButtonBar.OK);
		}
		else
		{
			// if no words found at all, splash up a message box and reset the search position
			// no matching text found
			msgbox = new UIMessageBox(parentFrame, 
				JNotePad.loadString(ResourceIDs.IDS_MSGFINDTEXT),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOMATCH),
				UIMessageBox.INFORMATION, UIButtonBar.OK);
		}
		
		msgbox.doModal();
		
		// get focus back to us
		// requestFocus();			
		
		startNewSearch();
		
		return false;
	}
	
	/**
	*	Overrides UIFindReplaceDialog.doReplace(). Calls search() to do searching,
	*	and replaces the found word. If no more words are left to find, displays a 
	*	dialog box informing the user of this.
	*
	*	@returns	true if a word was replaced, false if not.
	*/
	public boolean doReplace()
	{
        // start searching from the current selected text
		int iSelStart = textTarget.getSelectionStart();
		
		if (iSelStart != textTarget.getSelectionEnd())
		{
			iCurrentSearchPos = iSelStart;
		}
		
		// find the index of the next search hit
		int iHitStart = search();
		
		// if word is found
		if (iHitStart > -1)
		{
			int iFindTextLen = getFindText().length();
			
			// select the found text
			textTarget.setSelection(iHitStart, iHitStart+iFindTextLen);
			textTarget.moveTheCaret(iHitStart+iFindTextLen);
			
			// paste over it to replace it
			textTarget.paste(getReplaceText());
            iCurrentSearchPos = iHitStart + getReplaceText().length();
			return true;
		}
		
		UIMessageBox msgbox = null;
		if (iNumHits > 0)
		{
			// if word not found, splash up a message box and reset the search position
			// replacing done
			msgbox = new UIMessageBox(parentFrame, 
				JNotePad.loadString(ResourceIDs.IDS_MSGREPLACETEXT),
				JNotePad.loadString(ResourceIDs.IDS_MSGREPLACEDONE),
				UIMessageBox.INFORMATION, UIButtonBar.OK);
		}
		else
		{
			// if no more words found, splash up a message box and reset the search position
			// no matching text found
			msgbox = new UIMessageBox(parentFrame, 
				JNotePad.loadString(ResourceIDs.IDS_MSGREPLACETEXT),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOMATCH),
				UIMessageBox.INFORMATION, UIButtonBar.OK);
		}
		
		msgbox.doModal();
		
		// get focus back to us
		// requestFocus();
		
		startNewSearch();
		return false;
	}
	
	/**
	*	Overrides UIFindReplaceDialog.doReplaceAll(). Calls doReplace() until it
	*	returns false, which means all words have been replaced.
	*
	*	@returns	true
	*/
	public boolean doReplaceAll()
	{
        iCurrentSearchPos = 0;
		while (doReplace() == true)
            ;

		return true;
	}
	
	/**
	*	Informs the find replace dialog that we are starting a new search.
	*	This is used so we know when a search has failed completely.
	*/
	public void startNewSearch()
	{
		iCurrentSearchPos = NO_CURRENT_SEARCH;
		iNumHits = 0;
	}
	
	/**
	*	Overrides display. Calls the default display() function and then
	*	sets focus to the find next button.
	*/
	public int display(int style)
	{
		int iRet = super.display(style);
		
		// set focus to the find/replace dialog
		requestFocus();
		
		return iRet;
	}
	
	/**
	*	Searches the text in textTarget. Uses String.indexOf() to do searching;
	*	very slow, yes, but simple. Replace this with a Boyer-Moore search for speed.
	*
	*	@returns	the character index of the word that was found, or -1 if no word was found.
	*/
	protected int search()
	{			
		String str = textTarget.getText();
		String findText = getFindText();
		
		// check if this is the first time we're searching
		if (iCurrentSearchPos == NO_CURRENT_SEARCH)
		{
			// set it to the beginning of the file if we're
			// searching forward, or to the end of the
			// file if we're searching backward
			if (isForward())
			{
				iCurrentSearchPos = 0;
			}
			else
			{
				iCurrentSearchPos = str.length()-1;
			}													   
		}
		
		int iIndex = -1;		
		
		if (!isCaseSensitive())
		{
			str = str.toLowerCase();
			findText = findText.toLowerCase();					
		}
		
		if (isForward())
		{
			// do the searching forward
			iIndex = str.indexOf(findText, iCurrentSearchPos);
			iCurrentSearchPos = iIndex+1;
		}
		else
		{
			// do the searching backwards					
			iIndex = str.lastIndexOf(findText, iCurrentSearchPos);
			iCurrentSearchPos = iIndex-1;
		}
		
		if (iIndex < 0)
		{
			return iIndex;
		}
		

		if (isWholeWord())
		{					
			// let's see if the characters before and after this hit
			// are token separators
			
			if (iIndex > 0)
			{
				char c = str.charAt(iIndex-1);
				if (Character.isLetter(c) || c == '\'')
				{
					// letters or an apostraphe are not valid word delimiters.
					// everything else separates words (punctuation, white space)
					
					// since this isn't a valid hit, run the search again.
					// The whole file will eventually be searched, so this
					// won't recurse forever.
					
					return search();
				}
			}
			
			int iFindTextEndIndex = findText.length()+iIndex;
			
			if (iFindTextEndIndex < str.length()-1)
			{
				char c = str.charAt(iFindTextEndIndex+1);
				if (Character.isLetter(c) || c == '\'')
				{
					// letters or an apostraphe are not valid word delimiters.
					// everything else separates words (punctuation, white space)
					
					// since this isn't a valid hit, run the search again.
					// The whole file will eventually be searched, so this
					// won't recurse forever.
					
					return search();
				}
			}
		}
		
		if (iIndex > -1)
		{
			++iNumHits;
		}
		
		return iIndex;
	}
}

