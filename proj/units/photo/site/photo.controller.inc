<?php

	namespace Proj\Site\Units;

	require DIR_UNITS . 'photo/site/photo.actions.inc';
	require DIR_UNITS . 'photo/site/photo.model.inc';

	require DIR_UNITS . 'photo/site/views/forMain.tpl';
	require DIR_UNITS . 'photo/site/views/forTour.tpl';
	require DIR_UNITS . 'photo/site/views/albums.tpl';
	require DIR_UNITS . 'photo/site/views/album.tpl';

	use Base\Instance;
	use Proj\Site\Actions;
	use Proj\Site\Model;
	use Proj\Site\Templates as TPLs;

	class Photo extends Actions\Photo {
		use Instance;

		private function __construct() {
			parent::__construct(__FILE__);
		}

		public function HeaderForAlbums(): string {
			$image = Model\General::instance()->GetImage('photo');
            $subhead = Model\General::instance()->GetText('subhead_photo');

			return TPLs\General\HeaderForPages::ToVar($image, 'Фотоальбомы', $subhead);
		}

		public function HeaderForItem(int $id): string {
			$header = Model\Photo::instance()->GetAlbumHeader($id);
			$image = Model\General::instance()->GetImage('photo');

			return TPLs\General\HeaderForPages::ToVar($image, $header, '');
		}

		public function Albums(): string {
			$albums = Model\Photo::instance()->GetAlbums();

			return TPLs\Photo\Albums::ToVar($albums);
		}

		public function Album(): string {
			if (!$id = GetInt('id')) return '';

			$photos = Model\Photo::instance()->GetPhotoByAlbumID($id);
			if (!$photos) return '';

			return TPLs\Photo\Album::ToVar($photos);
		}

		public function ForTour(int $albumId): string {
			$photos = Model\Photo::instance()->GetPhotoByAlbumID($albumId, 6);
			if (!$photos) return '';

			return TPLs\Photo\ForTour::ToVar($photos, $albumId);
		}

		public function ForMain(): string {
			$photos = Model\Photo::instance()->GetAlbums(10);

			return $photos ? Tpls\Photo\ForMain::ToVar($photos) : '';
		}

	}

	Photo::init();