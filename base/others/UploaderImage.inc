<?php

	namespace Proj\Others;

	use \GdImage;
	use \Exception;

	class UploaderImage {
		const SIZE_ORIGINAL				= 1;
		const SIZE_COVER				= 2;
		const SIZE_CONTAIN				= 3;

		const ERROR_FORMAT				= 'Wrong file format';

		private string 		$source_path;
		private string 		$source_type;
		private int 		$source_width;
		private int 		$source_height;
		private float 		$source_ratio;
		private GdImage		$source_image;

		private int 		$quality			= 75;
		private ?int 		$width				= null;
		private ?int 		$height				= null;
		private int 		$size;

		/**
		 * @throws Exception
		 */
		public function __construct(string $path_img, $type = null) {
			$this->source_path = $path_img;

			if ($type) {
				$this->source_type = $type;
			} else {
				$info = pathinfo($this->source_path);
				$this->source_type = strtolower($info['extension']);
			}

			if (!$this->CheckType()) throw new Exception(self::ERROR_FORMAT);
			$this->source_image = $this->GetImage();
			$this->CalcOriginalSize();
		}

		public function Save(string $path, string $name, $type = null, ?int $width = null, ?int $height = null, int $size = self::SIZE_ORIGINAL, $quality = 75): array {
			$this->width = $width;
			$this->height = $height;
			$this->size = $size;
			$this->quality = $quality;
			if (!$width || !$height) $this->size = self::SIZE_ORIGINAL;

			[$work_width, $work_height] = $this->GetSize();
			return $this->CreateImage($path, $name, $type ? strtolower($type) : $this->source_type, $work_width, $work_height);
		}

		private function CheckType(): bool {
			return (in_array($this->source_type, ['jpeg', 'jpg', 'png', 'gif', 'bmp', 'webp']));
		}

		private function GetImage(): GdImage {
			return match ($this->source_type) {
				'jpeg', 'jpg' => imagecreatefromjpeg($this->source_path),
				'png' => imagecreatefrompng($this->source_path),
				'gif' => imagecreatefromgif($this->source_path),
				'bmp' => imagecreatefrombmp($this->source_path),
				'webp' => imagecreatefromwebp($this->source_path)
			};
		}

		private function CalcOriginalSize(): void {
			[$this->source_width, $this->source_height] = getimagesize($this->source_path);
			$this->source_width = (int)$this->source_width;
			$this->source_height = (int)$this->source_height;
			$this->source_ratio = ($this->source_height / $this->source_width);
		}

		private function GetSize(): array {
			return match ($this->size) {
				self::SIZE_ORIGINAL => [$this->source_width, $this->source_height],
				self::SIZE_COVER => $this->GetSizeCover($this->source_width, $this->source_height, $this->source_ratio),
				self::SIZE_CONTAIN => $this->GetSizeContain($this->source_width, $this->source_height, $this->source_ratio)
			};

		}

		private function GetSizeCover(int $source_width, int $source_height, float $source_ratio): array {
			if (($source_height > $this->width) && ($source_height > $this->height)) {
				$incr_w = $source_width / $this->width;
				$incr_h = $source_height / $this->height;
				if ($incr_w > $incr_h) {
					$work_height = $this->height;
					$work_width = $work_height / $source_ratio;
				} else {
					$work_width = $this->width;
					$work_height = $work_width * $source_ratio;
				}
			} else {
				$work_width = $source_width;
				$work_height = $source_height;
			}

			return [$work_width, $work_height];
		}

		private function GetSizeContain(int $source_width, int $source_height, float $source_ratio): array {
			if (($source_width > $this->width) || ($source_height > $this->height)) {
				if ($this->width * $source_ratio > $this->height) {
					$work_height = $this->height;
					$work_width = $work_height / $source_ratio;
				} else {
					$work_width = $this->width;
					$work_height = $work_width * $source_ratio;
				}
			} else {
				$work_width = $source_width;
				$work_height = $source_height;
			}

			return [$work_width, $work_height];
		}

		private function CreateImage(string $path, string $name, string $type, float $work_width, float $work_height): array {
			$work_image = imagecreatetruecolor($work_width, $work_height);
			imagecopyresampled($work_image, $this->source_image, 0, 0, 0, 0, $work_width, $work_height, $this->source_width, $this->source_height);

			$full_name = "{$path}{$name}.{$type}";

			$exif = @exif_read_data($this->source_path);
			if (isset($exif, $exif['Orientation']) && $exif['Orientation'] != '') {
				$work_image = match ($exif['Orientation']) {
					8 => imagerotate($work_image, 90, 0),
					3 => imagerotate($work_image, 180, 0),
					6 => imagerotate($work_image, - 90, 0),
					default => $work_image
				};
			}

			switch ($type) {
				case 'jpeg': case 'jpg': imagejpeg($work_image, $full_name, $this->quality); break;
				case 'png': imagepng($work_image, $full_name); break;
				case 'gif': imagegif($work_image, $full_name); break;
				case 'bmp': imagebmp($work_image, $full_name); break;
				case 'webp': imagewebp($work_image, $full_name); break;
			}

			return [
				'path' => $path,
				'name' => $name,
				'type' => $type,
				'full_name' => $full_name
			];
		}

	}