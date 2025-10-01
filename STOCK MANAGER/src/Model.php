<?php
namespace App;

use App\Database;
use PDO;

class Model {
    protected $db;

    public function __construct() {
        $this->db = Database::getInstance();
    }
}
