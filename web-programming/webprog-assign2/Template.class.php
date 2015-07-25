<?php
require_once("includes.inc.php");

class Template implements ITemplate {

	public $names;
	public $output;
	public $tag_names;

	public function __construct ($fileName)  {
		
		$matches;

	
		if (file_exists($fileName))
		{
			
			$this->output=file_get_contents($fileName);
		}
		
		else {
			throw new NoSuchTemplateFileException();
		}
	
		//preg_match_all ("{{{[a-zA-Z])+name(:|_|(\s))([a-zA-Z0-9(\s)])+}}}", $this->output, $matches);
		preg_match_all ("{{{([a-zA-Z])*name(:|_|(\s))([a-zA-Z0-9(\s)])*}}}", $this->output, $matches);

		foreach($matches[0] as $index=>$data)
		{
			if ( substr(trim($data), 2, 4) != "name")
			{
				echo "<br> template invalid syntax";
				throw new InvalidTemplateSyntaxException();
			}

			if ( substr(trim($data), 6, 1) != ":")
			{
				echo " template invalid syntax";
				throw new InvalidTemplateSyntaxException();
			}

			if (trim(substr(trim($data), 7, -2)) == "")
			{
				echo "<br> template invalid syntax";
				throw new InvalidTemplateSyntaxException();
			}

			//echo " ".$index." ".$data."<br>";
			$this->names[trim(substr(trim($data), 7, -2))] = "";
			$this->tag_names[$index]=trim(substr(trim($data), 7, -2));
		}
	}

	public function __set ($name, $value) {

		echo "<br> in set name = ".$name." in <br>";
		print_r($this->names);
		echo "<br>";

		if (!array_key_exists($name, $this->names))
		{
			echo "<br> tag doesn't exist in names <br>";
			throw new NoSuchTagNameException();
			
		}
		else {
			$this->names[$name]=$value;
		}
	}

	public function getTagNames() {
		
		echo "<br> names <br>";

		return $this->tag_names;

	}

	public function display () {

		foreach($this->names as $tag=>$data)
		{
			echo "<br> [display] ".$data."<br>";
			if ($data != "")
			{
				$data=(file_exists($data))?$this->parseFile($data):$data;
				//$this->output=str_replace('{{name:'.$tag.'}}',$data,$this->output);
				$this->output=preg_replace("{{{(\s)*name(\s)*:(\s)*".$tag."(\s)*}}}",$data,$this->output);
			}
			else
			{
				echo "<br> no tag value exception <br>";
				throw new NoTagValueException();
				
			}
		}

		echo htmlentities($this->output);

	}

	function parseFile($file)
	{
		ob_start();
		include($file);
		$content=ob_get_contents();
		ob_end_clean();
		return $content;
	}


	public function render () {

	
		foreach($this->names as $tag=>$data)
		{
			echo "[render] ".$data."<br>";
			if ($data != "")
			{
				$data=(file_exists($data))?$this->parseFile($data):$data;
				//$this->output=str_replace('{{name:'.$tag.'}}',$data,$this->output);
				$this->output=preg_replace("{{{(\s)*name(\s)*:(\s)*".$tag."(\s)*}}}",$data,$this->output);
			}
			else
			{
				echo "no tag value exception <br>";
				throw new NoTagValueException();
				
			}
		}
		
		return $this->output;
	}

}
/*
$template = new Template("myTemplate.tpl.html");
$matches = $template->getTagNames();
print_r($matches);
$template->title = "Titlul meu";
$template->content = "Hello World !";

echo "<br>".htmlentities($template->render());
$template->display();*/
?>