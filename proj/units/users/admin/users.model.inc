<?php

    namespace Proj\Admin\Model;

    use Base\Instance;

    class Users {
        use Instance;

        private static string | null $uid = null;
        private static bool $login = false;

        private function __construct() { $this->CheckSession(); }

        private function CheckSession(): void {
            if (isset($_SESSION['USERS'])) {
                self::$login = $_SESSION['USERS']['LOGIN'] ?? false;
            }
        }

        public function PasswordHash($pass): string {
            return md5($pass);
        }

        public function Login(): void {
            $_SESSION['USERS']['LOGIN'] = true;
        }

        public function Logout(): void {
            $_SESSION['USERS']['LOGIN'] = false;
        }

        public function IsLogin(): bool {
            return self::$login;
        }

    }

Users::init();