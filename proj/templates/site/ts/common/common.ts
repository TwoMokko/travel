/**
 * Навигация по турам на странице "tours"
 * @param selector
 * @param top_absolute
 * @param top_fixed
 * @constructor
 */
function NavigationTour(selector: string, top_absolute: number, top_fixed: number): void {
	let $document = $(document);
	let $selector = $(selector);
	let $parent = $selector.parent();

	$document.on('scroll', Redraw);

	function Redraw(): void {
		let _top = $parent.offset().top;
		let _scroll = $document.scrollTop();

		if (_top + (top_absolute - top_fixed) <= _scroll) $selector.css({position: 'fixed', top: `${top_fixed}px`});
		else $selector.css({position: 'absolute', top: `${top_absolute}px`});
	}

	Redraw();
}

/**
 * Появление кнопки для рокрутки страницы наверх
 * @param selector
 * @constructor
 */
function ScrollTop(selector: string): void {
	/*Elements*/
	let $document = $(document);
	let $elem = $(selector);
	let $button = $('<span/>', { class: 'arrow_top' });

	/*Building DOM*/
	$elem.append($button);

	/*Events*/
	$document.on('scroll', Redraw);
	$button.on('click', () => { $document.scrollTop(0); });

	function Redraw(): void {
		let _top = $elem.offset().top;
		let _scroll = $document.scrollTop();
		(_top < _scroll) ? $button.addClass('show') : $button.removeClass('show');
	}

	Redraw();
}

type TypeTour = {[key: number]: { name: string, href: string } }
type TypeCategory = {[key: number]: { name: string, tours: TypeTour } };


/**
 * Работа с селектами на главной странице
 */
class SelectTour {
	data: TypeCategory;

	$select_categories: JQuery;
	$select_tours: JQuery;
	$btn_see_tour: JQuery;

	constructor(data: TypeCategory) {
		this.data = data;

		this.$select_categories = $('#categories');
		this.$select_tours = $('#tours');
		this.$btn_see_tour = $('#see_tour');

		this.$select_categories.attr('autocomplete', 'off');
		this.$select_tours.attr('autocomplete', 'off');

		this.$select_categories.on('change', this.RestructureTours.bind(this));
		this.$select_tours.on('change', this.RestructureBtn.bind(this));

		this.RestructureCategory();
	}

	private RestructureCategory(): void {
		for (let i in this.data) {
			if (IsEmpty(this.data[i].tours)) continue;
			this.$select_categories.append(
				$('<option/>', {value: i}).text(this.data[i].name)
			);
		}
		this.$select_categories.trigger('change');
	}

	private RestructureTours(): void {
		let category = Number(this.$select_categories.val());

		this.$select_tours.empty();
		if (!category) return;
		for (let i in this.data[category].tours) {
			this.$select_tours.append(
				$('<option/>', {value: i}).text(this.data[category].tours[i].name)
			);
		}
		this.$select_tours.trigger('change');
	}

	private RestructureBtn(): void {
		let category = this.$select_categories.val().toString();
		let tour = this.$select_tours.val();
		this.$btn_see_tour.attr('href', this.data[category].tours[tour].href);
	}

}


function Switcher(selector_menu, selector_list) {
	let $menu = $(selector_menu);
	let $list = $(selector_list);

	$menu.find('> *:first-child').addClass('active');
	$list.find('> *:not(:first-child)').addClass('hide');

	$menu.children().each((key, elem) => {
		let $elem = $(elem);
		$(elem).on('click', () => DoSwitch(key, $elem));
	});

	function DoSwitch(key, $elem): void {
		$menu.children().removeClass('active');
		$elem.addClass('active');

		$list.children().addClass('hide');
		$list.find(`> *:nth-child(${key + 1})`).removeClass('hide');
	}

}

/**
 * Вывод формы обратной связи через кнопку "поехать" в "tours"
 * @constructor
 */
function ToDrive(tour_id): void {
	let $form = $('<form/>', {class: '', action: '/feedback/add'});
	let $name = $('<input/>', {name: 'name', class: '', type: 'text', placeholder: 'Имя*', minlength: '3', maxlength: '50'});
	let $call = $('<input/>', {name: 'contact', class: '', type: 'text', placeholder: 'Способ связи*', minlength: '3', maxlength: '50'});
	let $send = $('<a/>', {class: 'button', text: 'Отправить'});

	$send.on('click', () => {
		if (Validation.Form($form)) Base.Common.Query.SendForm($form, Success);
	});

	$form.append(
		$('<input/>', {name: 'tour_id', type: 'hidden', value: tour_id}),
		$name,
		$call,
		$send
	);

	let wind = Common.Window.Create('Оставьте заявку', $form);


	function Success(): void {
		wind.Close();
		Common.Window.ShowMessage('Спасибо, ваша заяка принята');

	}
}


/**
 * Вывод формы обратной связи через кнопку "поехать" в "tours"
 * @constructor
 */
function LeaveReview(avatars): void {
	let $form 				= $('<form/>', {class : '', action: '/review/add'});
	let $name 				= $('<input/>', {name: 'name', class : '', type : 'text', placeholder : 'Имя*', minlength: '3', maxlength: '50'});
	let $text_container 	= $('<div/>', {class : ''});
	let $text 				= $('<textarea/>', {name: 'text', class : '', type : 'text', placeholder : 'Напишите отзыв*', rows: '5', maxlength: '255'});
	let $avatar_container 	= $('<span/>', {class : 'avatar_container'});
	let $send 				= $('<a/>', {class : 'button', text : 'Отправить'});

	$send.on('click', () => {
		if (Validation.Form($form)) Base.Common.Query.SendForm($form, Success);
	});

	for (let i in avatars) {
		let $label = $('<label/>', {class: ''});
		let $ava = $('<div/>', {class: 'ava'});
		let $radio = $('<input/>', {type: 'radio', class: 'hide', value: i, name: 'avatar'});

		$ava.css('background-image', `url(${avatars[i]})`).on('click', () => {
			$avatar_container.find('.active').removeClass('active');
			$ava.hasClass('active') ? $ava.removeClass('active') : $ava.addClass('active');
		});

		$avatar_container.append(
			$label.append(
				$ava,
				$radio
			)
		)
	}

	$form.append(
		$name,
		$text_container.append($text),
		$avatar_container,
		$send
	);

	let wind = Common.Window.Create('Оставьте отзыв', $form);

	function Success(): void {
		wind.Close();
		Common.Window.ShowMessage('Спасибо за отзыв');

	}
}

function ShowVideo(): void {
	console.log('123');
	let $iframe			= $('<iframe/>', {class: 'show_video', src: 'https://www.youtube.com/embed/XDziNYkyFww', allowfullscreen: '', frameborder: 0});
	let $video			= $('<video/>', {class: 'show_video', controls: 'controls'});
	let $source			= $('<source/>', {src: 'https://youtu.be/XDziNYkyFww'});

	// $video.append($source);
	Common.Window.Create('Смотреть видео', $iframe);
	$iframe.parent().removeClass('container');
}

class Validation {

	static Form($form: JQuery): boolean {
		let $check = true;
		let $elements = $form.find('input[type="text"], textarea');
		$elements.each((i, element) => {
			let value = '';
			switch ($(element).prop('nodeName')) {
				case 'INPUT': value = $(element).val().toString(); break;
				case 'TEXTAREA': value = $(element).text(); break;
			}
			if (!Validation.Element($(element), value)) $check = false;
		});
		return $check;
	}

	static Element($element: JQuery, value: string): boolean {
		let errors = [];

		let minlength = $element.attr('minlength');
		if ((minlength != undefined) && (value.trim().length < Number(minlength))) errors.push(`Не менее ${minlength} символов`);

		let maxlength = Number($element.attr('maxlength'));
		if ((maxlength != undefined) && (value.trim().length > Number(maxlength))) errors.push(`Не более ${maxlength} символов`);

		if (errors.length) {
			Validation.ShowErrors($element, errors);
			return false;
		}

		Validation.HideErrors($element);
		return true;
	}

	static ShowErrors($element: JQuery, errors: string[]): void {
		// $element.next('.validation_error').remove();
		// let $errors = $('<span/>', {class: 'validation_error', title: errors.join(`\n`)});
		// $element.after($errors);
		$element.addClass('error');
	}

	static HideErrors($element: JQuery): void {
		// $element.next('.validation_error').remove();
		$element.removeClass('error');
	}

}

/**
 * Вывод окна после отправки данных пользователем
 * @constructor
 */
function AfterSend(): void {
	Common.Window.ShowMessage('Спасибо, ваша заяка принята');
}

function GetReview(path, id) {
	Base.Common.Query.SendData(path, {id: id}, ShowReview);
}

function ShowReview(data) {
	let $review = $('<div/>', {class: 'review_window'});

	$review.append(
		$('<div/>', {class: 'review_person'}).append(
			$('<div/>').css('background-image', `url(${data['image']})`),
			$('<div/>').text(data['name'])
		),
		$('<div/>', {class: 'review_text'}).text(data['text'])
	);

	Common.Window.Create('✎', $review);
}

namespace Common {

	/**
	 * Менеджер работы с окнами
	 */
	export class Window {
		private static windows = {};
		private static iter = 0;
		public static $windows = null;

		public static ShowMessage(text: string): Instance {
			return Window.Create(null, text);
		}

		public static Create(title: string | null = null, content: JQuery | string): Instance {
			if (!Window.$windows) {
				Window.$windows = $('<div/>', {class : 'windows'});
				$('main').append(
					Window.$windows
				);
			}

			let id = ++Window.iter;
			let wind = new Instance(id, title, content);
			Window.windows[id] = wind;
			return wind;
		}

		public static Remove(id: number): void {
			delete Window.windows[id];
		}

	}

	/**
	 * Работа с окнами
	 */
	class Instance {
		private readonly id: number;
		private readonly $instance: JQuery;

		constructor(id: number, title: string | null, content: JQuery | string) {
			this.id = id;
			this.$instance = $('<div/>', { class : 'instance' });
			let $space = $('<div/>', { class : 'space' });
			let $window = $('<div/>', { class : 'window' });
			let $header = $('<div/>');
			let $title = $('<div/>', { class : 'title' });
			let $close = $('<div/>', { class : 'close' });
			let $container = $('<div/>');

			(title !== null) ? $header.addClass('head') : $header.addClass('head_null_title');
			(title !== null) ? $container.addClass('container') : $container.addClass('container_null_title');

			this.$instance.append(
				$space,
				$window.append(
					$header.append(
						(title !== null) ? $title.append(title) : $(),
						$close
					),
					$container.append(content)
				)
			);

			$space.on('click', this.Close.bind(this));
			$close.on('click', this.Close.bind(this));

			Window.$windows.append(this.$instance);
		}

		public Close(): void {
			this.$instance.remove();
			this.Remove();
		}

		private Remove(): void {
			Window.Remove(this.id);
		}

	}

}

/**
 * Работа с просмотрщиком фотографий
 */
class Gallery {
	/* Variables */
	images					: string[];
	active					: number;

	/* Elements */
	$th						: JQuery;
	$gallery				: JQuery;
	$photo					: JQuery;

	imageWidth				: number;
	imageHeight				: number;
	percent					: number;

	constructor(th: HTMLElement) {
		this.$th = $(th);
		this.percent = 0.8;

		if (!this.SearchImages()) return;

		/* Set elements */
		this.$gallery = $('<div/>', {class: 'gallery'});
		this.$photo = $('<span>', {class: 'photo_gallery'});
		let $space = $('<div/>', {class: 'space'});
		let $container_btn = $('<div/>', {class: 'container_btn'});
		let $close = $('<span>', {class: 'close'});
		let $arrow_left = $('<span>', {class: 'arrow_left'});
		let $arrow_right = $('<span>', {class: 'arrow_right'});



		/* Building DOM */
		$('main').append(
			this.$gallery.append(
				$space,
				this.$photo,
				$container_btn.append(
					$close,
					(this.images.length > 1) ? $arrow_left : $(),
					(this.images.length > 1) ? $arrow_right : $()
				)
			)
		);

		/* Events */
		$space.on('click', this.Close.bind(this));
		$close.on('click', this.Close.bind(this));
		$arrow_left.on('click', this.Left.bind(this));
		$arrow_right.on('click', this.Right.bind(this));
		$(window).on('resize', {self: this}, Gallery.OnResize);
		$(document).on('keydown.gallery', this.OnKeyDown.bind(this));

		this.ShowImage();
	}

	/**
	 *
	 * @param e
	 * @constructor
	 * @private
	 */
	private static OnResize(e): void {
		let self : Gallery = e.data.self;
		self.NewSize(self);
	}

	/**
	 *
	 * @param e
	 * @constructor
	 * @private
	 */
	private OnKeyDown(e): boolean {
		switch (e.originalEvent.keyCode) {
			case 39: this.Right(); break;
			case 32: this.Right(); return false;
			case 37: case 8: this.Left(); break;
			case 27: this.Close(); break;
		}
		return true;
	}

	/**
	 *
	 * @constructor
	 * @private
	 */
	private SearchImages(): boolean {
		this.images = [];

		let id = this.$th.data('id');
		let $images = $(`[data-id=${id}]`);

		this.active = 0;

		$images.each((key, element) => {
			let $element = $(element);
			this.images.push($element.data('url'));
			if ($element.is(this.$th)) this.active = key;
		});

		return !!this.images.length;
	}

	/**
	 * Показать фотографию
	 * @constructor
	 * @private
	 */
	private ShowImage(): void {
		this.$photo.css('background-image', `url(${this.images[this.active]})`);

		this.GetSize();
	}

	/**
	 *
	 * @constructor
	 * @private
	 */
	private GetSize(): void {
		let img = new Image();
		img.src = this.images[this.active];
		img.onload = () => {
			this.imageWidth = img.width;
			this.imageHeight = img.height;

			this.NewSize(this);
		};
	}

	/**
	 *
	 * @param self
	 * @constructor
	 * @private
	 */
	private NewSize(self: Gallery): void {
		let gallerySize = [self.$gallery.width(), self.$gallery.height()];
		let newSize = self.GetNewSize(gallerySize);
		this.Resize(newSize);
	}

	/**
	 *
	 * @param gallerySize
	 * @constructor
	 * @private
	 */
	private GetNewSize(gallerySize): [number, number] {
		let resultWidth = this.imageWidth;
		let resultHeight = this.imageHeight;
		let a = this.imageWidth / this.imageHeight;

		if (this.imageWidth > (gallerySize[0] * this.percent) || this.imageHeight > (gallerySize[1] * this.percent)) {
			if (this.imageWidth / gallerySize[0] > this.imageHeight / gallerySize[1]) {
				resultWidth = gallerySize[0] * this.percent;
				resultHeight = resultWidth / a;
			}
			else {
				resultHeight = gallerySize[1] * this.percent;
				resultWidth = resultHeight * a;
			}
		}

		return [resultWidth, resultHeight];
	}

	/**
	 *
	 * @param size
	 * @constructor
	 * @private
	 */
	private Resize(size: [number, number]): void {
		this.$photo.css({width: `${size[0]}px`, height: `${size[1]}px`});
	}


	/**
	 * Закрыть галерею и очистить данные
	 * @constructor
	 */
	public Close(): void {
		this.$gallery.remove();
		$(window).off('resize', Gallery.OnResize);
		$(document).off('keydown.gallery');
	}

	/**
	 * Листать фотографию влево
	 * @constructor
	 */
	public Left(): void {
		this.active = (this.active) ? this.active - 1 : this.images.length - 1;

		this.ShowImage();
	}

	/**
	 * Листать фотографию вправо
	 * @constructor
	 */
	public Right(): void {
		this.active = (this.active !== this.images.length - 1) ? this.active + 1 : 0;

		this.ShowImage();
	}
}

class Menu {
	$container			: JQuery;

	constructor(th: HTMLElement) {
		/* Set elements */
		this.$container = $('<div/>', {class: 'mini_menu'});
		let $space = $('<div/>', {class: 'space'});
		let $content = $('<div/>', {class: 'content_menu'});
		let $close = $('<div/>', {class: 'close_menu'});
		let $pages = $('<div/>', {class: 'pages_menu'});
		let $div1 = $('<div/>');
		let $div2 = $('<div/>');
		let $div3 = $('<div/>');
		let $div4 = $('<div/>');
		let $div5 = $('<div/>');
		let $div6 = $('<div/>');
		let $page1 = $('<a/>', {class: 'page1', text: 'Главная', href: '/'});
		let $page2 = $('<a/>', {class: 'page2', text: 'Путешествия', href: '/tours'});
		let $page3 = $('<a/>', {class: 'page3', text: 'О нас', href: '/about'});
		let $page4 = $('<a/>', {class: 'page4', text: 'Дневник путешествий', href: '/stories'});
		let $page5 = $('<a/>', {class: 'page5', text: 'Отзывы', href: '/review'});
		let $page6 = $('<a/>', {class: 'page5', text: 'Фотоальбомы', href: '/photo'});

		/* Building DOM */
		$('body').append(
			this.$container.append(
				$space,
				// $content.append(
					$close,
					$pages.append(
						$div1.append($page1),
						$div2.append($page2),
						$div3.append($page3),
						$div4.append($page4),
						$div5.append($page5),
						$div6.append($page6)
					)
				// )
			)
		);

		$space.on('click', this.Close.bind(this));
		$close.on('click', this.Close.bind(this));
		$('.open_menu').addClass('hide');
	}


	public Close(): void {
		this.$container.remove();
		$('.open_menu').removeClass('hide');
	}
}

class Carousel {
	/* Variables */
	active					: number;
	count					: number;

	/* Elements */
	$container		:JQuery;
	$wrap			:JQuery;
	$scroll			:JQuery;
	$items			:JQuery[];
	$manage			:JQuery;
	$array_left		:JQuery;
	$array_right	:JQuery;

	constructor(container: string) {
		/*  */
		this.$container = $(container);
		this.count = 1;
		this.$items = [];
		this.active = 0;

		this.$container.children().each((index, element) => {
			let $element = $(element);
			this.$items.push($element);
			$element.detach();
		});

		/* Set elements */
		this.$wrap = $('<div/>', {class: 'wrap'});
		this.$scroll = $('<div/>', {class: 'scroll'});
		this.$manage = $('<div/>', {class: 'manage'});
		this.$array_left = $('<div/>');
		this.$array_right = $('<div/>');

		/* Building DOM */
		this.$container.append(
			this.$manage.append(
				this.$array_left,
				this.$array_right
			),
			this.$wrap.append(
				this.$scroll
			)
		);

		/* Events */
		this.$array_left.on('click', () => {
			this.GetActive('left');
			this.ShowItems();
		} );
		this.$array_right.on('click', () => {
			this.GetActive('right');
			this.ShowItems();
		});

		this.$container.addClass('carousel');

		$(window).on('resize', this.Restructure.bind(this));
		this.Restructure();
	}

	private Restructure(): void {
		let gtc = this.$scroll.css('grid-template-columns');
		this.count = (gtc !== 'none') ? this.$scroll.css('grid-template-columns').split(' ').length : 1;

		if (this.count >= this.$items.length) {
			this.$array_left.addClass('hide');
			this.$array_right.addClass('hide');
		} else {
			this.$array_left.removeClass('hide');
			this.$array_right.removeClass('hide');
		}

		this.ShowItems();
	}

	private ShowItems(): void {
		this.$scroll.children().each((index, element) => {
			let $element = $(element);
			$element.detach();
		});
		for (let i = 0, a = this.active; i < this.count && i <= (this.$items.length - 1); i++) {
			this.ShowItem(a);
			a = this.GetNext(a);
		}
	}

	private ShowItem(a) {
		this.$scroll.append(this.$items[a]);
	}

	private GetNext(a): number {
		if (a >= (this.$items.length - 1)) return 0;
		else return ++a;
	}

	private GetActive(side): any {
		switch (side) {
			case('left'):
				if (this.active == 0) this.active = (this.$items.length - 1)
				else this.active--;
				break;
			case('right'):
				if (this.active == (this.$items.length - 1)) this.active = 0
				else this.active++;
				break;
		}
	}
}

function IsEmpty(obj: object): boolean {
	for (const objKey in obj) return false;
	return true;
}