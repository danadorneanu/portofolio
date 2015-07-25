<?php
	class NoSuchTemplateFileException extends Exception {
		protected $message = 'Template file not found';   // exception message
	}
	class InvalidTemplateSyntaxException extends Exception {
		protected $message = 'Template file contains syntax errors';
	}
	class NoSuchTagNameException extends Exception {
		protected $message ='Tag name does not exist in template';
	}
	class NoTagValueException extends Exception {
		protected $message ='Tag name has no specified value';
	}
?>