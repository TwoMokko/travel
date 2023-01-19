function NavigationTour(selector: string, top_absolute: number, top_fixed: number) {
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

function ScrollTop(selector: string) {
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

type TypeTour = { id: number, name: string, href: string }
type TypeCategory = { id: number, name: string, tours: TypeTour[] };

class SelectTour {
	data: TypeCategory[];

	$select_categories: JQuery;
	$select_tours: JQuery;
	$btn_see_tour: JQuery;

	constructor(data: TypeCategory[]) {
		this.data = data;

		this.$select_categories = $('#categories');
		this.$select_tours = $('#tours');
		this.$btn_see_tour = $('#see_tour');

		this.$select_categories.on('change', this.RestructureTours.bind(this));
		this.$select_tours.on('change', this.RestructureBtn.bind(this));

		this.RestructureCategory();
	}

	private RestructureCategory() {
		for (let i in this.data) {
			this.$select_categories.append(
				$('<option/>', {value: i}).text(this.data[i].name)
			);
		}

		this.$select_categories.trigger('change');
	}

	private RestructureTours() {
		let category = Number(this.$select_categories.val());

		this.$select_tours.empty();
		for (let i in this.data[category].tours) {
			this.$select_tours.append(
				$('<option/>', {value: this.data[category].tours[i].href}).text(this.data[category].tours[i].name)
			);
		}

		this.$select_tours.trigger('change');
	}

	private RestructureBtn() {
		this.$btn_see_tour.attr('href', this.$select_tours.val().toString());
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

	function DoSwitch(key, $elem) {
		$menu.children().removeClass('active');
		$elem.addClass('active');

		$list.children().addClass('hide');
		$list.find(`> *:nth-child(${key + 1})`).removeClass('hide');
	}

}

function ToDrive(): void {
	let $form = $('<form/>', {class : ''});
	let $name = $('<input/>', {class : '', type : 'text', placeholder : 'Имя*'});
	let $call = $('<input/>', {class : '', type : 'text', placeholder : 'Способ связи*'});
	let $send = $('<a/>', {class : 'button', text : 'Отправить'});

	$form.append(
		$name,
		$call,
		$send
	);

	let wind = Common.Window.Create('Оставьте заявку', $form);

	$send.on('click', Success);


	function Success(): void {
		$send.closest('form').submit();
		wind.Close();
		Common.Window.ShowMessage('Спасибо, ваша заяка принята');

	}
}

function AfterSend(send) {
	send.closest('form').submit();
	Common.Window.ShowMessage('Спасибо, ваша заяка принята');
}

namespace Common {

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

	class Instance {
		private readonly id: number;
		private readonly $instance: JQuery;

		constructor(id: number, title: string | null, content: JQuery | string) {
			this.id = id;
			this.$instance = $('<div/>', { class : 'instance' });
			let $space = $('<div/>', { class : 'space' });
			let $window = $('<div/>', { class : 'window' });
			let $header = $('<div/>', { class : 'head' });
			let $title = $('<div/>', { class : 'title' });
			let $close = $('<div/>', { class : 'close' });
			let $container = $('<div/>', { class : 'container' });

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
					$arrow_left,
					$arrow_right
				)
			)
		);

		/* Events */
		$space.on('click', this.Close.bind(this));
		$close.on('click', this.Close.bind(this));
		$arrow_left.on('click', this.Left.bind(this));
		$arrow_right.on('click', this.Right.bind(this));
		$(window).on('resize', this.NewSize.bind(this));

		this.ShowImage();
	}

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

	private ShowImage(): void {
		this.$photo.css('background-image', `url(${this.images[this.active]})`);

		this.GetSize();
	}

	private GetSize(): void {
		let img = new Image();
		img.src = this.images[this.active];
		img.onload = () => {
			this.imageWidth = img.width;
			this.imageHeight = img.height;

			this.NewSize();
		};
	}

	private NewSize(): void {
		let gallerySize = [this.$gallery.width(), this.$gallery.height()];
		let newSize = this.GetNewSize(gallerySize);
		this.Resize(newSize);
		console.log('работает');
	}

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

	private Resize(size: [number, number]): void {
		this.$photo.css({width: `${size[0]}px`, height: `${size[1]}px`});
	}



	public Close(): void {
		this.$gallery.remove();
	}

	public Left(): void {
		this.active = (this.active) ? this.active - 1 : this.images.length - 1;

		this.ShowImage();
	}

	public Right(): void {
		this.active = (this.active !== this.images.length - 1) ? this.active + 1 : 0;

		this.ShowImage();
	}
}