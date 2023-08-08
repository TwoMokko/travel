<?php

	namespace Proj\Admin\Units;

	require DIR_UNITS . 'users/admin/users.structure.inc';
    require DIR_UNITS . 'users/admin/users.model.inc';

    use JetBrains\PhpStorm\NoReturn;

    use Base\Instance;
    use Base\Controller;
    use Proj\Admin\Structure;
    use Proj\Admin\Model;
    use Proj\Admin\Templates\LayoutAuthorization;
    use Proj\Admin\Templates\TemplateAuthorization;
    use Proj\Admin\Templates\Users\FormAuthorization;
    use Proj\Params;

	class Users extends Structure\Users {
		use Instance;

        private Model\Users $model;

			private function __construct() {
				parent::__construct();

                $this->model = Model\Users::instance();

                Controller::instance()->void->Push(self::$auth, [$this, 'Auth']);
                Controller::instance()->void->Push(self::$exit, [$this, 'Exit']);
			}

        public function IsPossible(): void {
            if ($this->model->IsLogin() || ((Controller::$area == self::NAME) && (Controller::$part == 'auth'))) return;

            require DIR_PROJ . 'templates/admin/layoutAuthorization.inc';
            require DIR_PROJ . 'templates/admin/templateAuthorization.tpl';
            require DIR_UNITS . 'users/admin/views/FormAuthorization.tpl';

            LayoutAuthorization::instance()->header->Push('Вход в систему');
            LayoutAuthorization::instance()->main->Push(FormAuthorization::ToVar());
            LayoutAuthorization::instance()->footer->Push('© ' . Params::$site_name);

            TemplateAuthorization::Render();

            die;
        }

        #[NoReturn] public function Auth(): void {
            $login = GetParam('login', '');
            $password = GetParam('password', '');
            $hash = $this->model->PasswordHash($password);

            if (($login != USER_LOGIN) || ($hash != USER_PASSWORD)) {
                SendJSONError('Ошибка доступа');
            }

            $this->model->Login();

            SendJSONSuccess([]);
        }

        #[NoReturn] public function Exit(): void {
            $this->model->Logout();

            SendJSONSuccess([]);
        }

	}

    Users::init();