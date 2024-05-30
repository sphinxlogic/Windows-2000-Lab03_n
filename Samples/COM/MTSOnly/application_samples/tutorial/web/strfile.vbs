<%

	'File:		strFile.vbs
	'Overview:	Contains all text strings for this web app.
	'			Keeping these all in one place eases localization, and
	'			is generally a good programming practice.
	
	'This file is provided as part of the Microsoft Visual Studio 6.0 Samples

	'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
	'WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
	'INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
	'OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
	'PURPOSE.

	'Copyright (C) 1997, 1998 Microsoft Corporation, All rights reserved

	Dim 	ERROR_CREATING_BUS_AD, ERROR_CREATING_BUS_CUST, ERROR_RETRIEVING_CUST, _
			INVALID_START_DATE, ERROR_INSERTING_ADD, _
			AD_PLACED_SUCCESFULLY, ERROR_INSERTING_AD, ERROR_GETTING_CATEGORIES, _
			NO_CATEGORIES, ERROR_GETTING_PRICES, ERROR_UPDATING_CUSTOMER, _
			INVALID_CATEGORY, ERROR_DISPLAYING_ADS, NO_CATEGORY, NO_ADS, _
			ERROR_CREATING_OBJECT, DEFAULT_PROMPT, FILL_ALL_FIELDS, ERROR_INSERTING_CUSTOMER, _
			EXISTING_EMAIL, DATABASE_ERROR, NEW_USER, CONGRATULATIONS, _
			INCORRECT_PASSWORD, INCORRECT_PASSWORD2, TO_PLACE_AN_AD

	ERROR_CREATING_BUS_AD = "Error creating Bus_Ad Object"
	ERROR_CREATING_BUS_CUST = "Error creating Bus_Customer Object"
	ERROR_RETRIEVING_CUST = "Error retrieving customer information."
	INVALID_START_DATE = "The start date or end date you've entered is invalid."
	ERROR_UPDATING_CUSTOMER = "Error updating Customer Information"
	ERROR_INSERTING_ADD = "Error inserting Ad"
	AD_PLACED_SUCCESFULLY = "Ad placed successfully. New Ad ID is "
	ERROR_INSERTING_AD = "Sorry, a problem occurred while trying to insert the advertisement."
	ERROR_GETTING_CATEGORIES = "Error getting category information."
	NO_CATEGORIES = "No categories were found.  This may have been caused by an application error."
	ERROR_GETTING_PRICES = "Sorry, an error has occurred while getting price information"
	INVALID_CATEGORY = "The category you chose is not valid, or there are no cateogies to display."
	ERROR_DISPLAYING_ADS = "Error displaying Ads"
	NO_CATEGORY = "There is no category with ID#"
	NO_ADS = "There are no ads in the selected category of "
	ERROR_CREATING_OBJECT = "Error creating object: "
	DEFAULT_PROMPT = "Fill out all of the lines in the form below.<BR>" & _
				"This will set up your account and allow you to place ads."
	FILL_ALL_FIELDS = "You must fill out all of the form below.<BR>" & _
					 "Please fill out the missing data and then select Insert."
	ERROR_INSERTING_CUSTOMER = "Sorry, an error occurred while entering your information.  Please contact your system administrator"
	EXISTING_EMAIL = "That email address corresponds to an existing account. If you already have an account" &_
				"and have forgotten your password, please call us to have a new password assigned."
	DATABASE_ERROR = "An error occurred while trying to update the database.  Please contact your systems administrator."
	NEW_USER = "New User"
	CONGRATULATIONS = "Congratulations! You have successfully set up your account. <BR>Now enter your password to log in and place an ad."
	INCORRECT_PASSWORD = "Sorry, that password is incorrect. " & _
				"Please try your email address and password again, " & _
				"or click on " 
	INCORRECT_PASSWORD2 = "  to set up a new account."
	TO_PLACE_AN_AD = "To place an ad, you must first log in. " &_
									"<br>If you do not already have an " &_
									"account, or click on "

%>
	
	