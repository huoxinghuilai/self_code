<?php
	/*
	 * namespace home\csmpadmin\event;	
	 *
	 * use home\csmpadmin\event\job;
	 */

	//include __DIR__ . '/job.php';
	
	class event {
		public $handler;

		public function on(job $obj) {
			$this->handler[$obj->name] = $obj;
		}

		public function trigger($event_name) {
			foreach ($this->handler as $handle) {
				if (!strcmp($event_name, $handle->name)) {

					return $handle->exec();	
				}
			}
		}
	}
?>
