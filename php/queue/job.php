<?php
	/* 	
	 * namespace home\csmpadmin\event;
	 */

	class job {
		public $name;
		public $proc;

		public function exec() {
			echo "execute this event!";
			echo "\n";
			return ($this->proc)();
		}
	}
?>
