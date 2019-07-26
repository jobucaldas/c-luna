#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <math.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;
typedef struct {
	float x, y,  wx, tx;
	int frames, line, dir, jump,a[1], cs,chat,ignore,endline;
	IntRect rectA;
	Clock cut,ch;
}shadow;

void init_main(shadow* main) {
	main->endline = 0;

	main->cs = 0;
	main->x = 235;
	main->y = 66 * 5;
	main->line = 1;
	main->dir = 1;
	main->frames = 4;
	main->jump = 0;
	
	IntRect a(0, 0, 160, 120);
	main->a[0] = 0;

}

int cutscene(Clock clock,IntRect* rectSourceSprite, Sprite* sprite, int sizex, int sizey, int frames, int line ,int fps) {
	if (((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)sizex < frames) {
		(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * sizex;
		(*rectSourceSprite).top = line * sizey;
		(*sprite).setTextureRect(*rectSourceSprite);
		return 1;
	}
	
	return 0;
}

void animate(Clock clock, IntRect* rectSourceSprite, Sprite* sprite, int sizex,int sizey, int frames, int line, int fps) {

	(*rectSourceSprite).left = ((int)(clock.getElapsedTime().asMilliseconds() / (1000.0 / fps))) % (int)frames * sizex ;
	(*rectSourceSprite).top = line * sizey;
	(*sprite).setTextureRect(*rectSourceSprite);

}

void write(int n, RenderWindow* window,float size, Color c,float x, float y,int i,string str) {
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	Text texto;
	texto.setFont(font);
	texto.setFillColor(c);
	texto.setPosition((*window).getSize().x /800*x, (*window).getSize().y /600*y);
	texto.setCharacterSize((*window).getSize().y * size);
	string s = std::to_string(i);
	switch (n)
	{
	case 0:
		texto.setString(s);
		break;
	case 1:
		texto.setString(str);
		break;
	default:
		texto.setString(" ");
	}

	(*window).draw(texto);
}

void chat(int n, RenderWindow* window) {
	switch (n) {
	case 0:
		write(1, window, 0.03, Color::White, 350, 650, 10, "Está muito escuro aqui...\n");
		write(1, window, 0.02, Color::White, 350, 650, 10, "\n \n ainda bem que há uma lanterna\n ..... o que é aquilo?");
		break;
	case 2:

		write(1, window, 0.03, Color::White, 50, 650, 10, "algo ainda me deixa desconfortavel aqui...");
		break;

	case 4:
		write(1, window, 0.03, Color::White, 50, 650, 10, "FUJA!	FUJA!  FUJA RAPIDAMENTE! ,\n ELE NÃO ESTÁ TÃO LONGE...");
		break;
	case 6:
		write(1, window, 0.03, Color::White, 50, 650, 10, "SAIA DO MEU QUARTO,\n crianças não deveriam estar aqui...");
		break;
	case 8:
		write(1, window, 0.08, Color::White, 50, 650, 10, "*****ROOOONCO******");
		break;

	case 10:
		write(1, window, 0.03, Color::White, 50, 650, 10, "nada aqui");
		break;

	case 101:
		write(1, window, 0.03, Color::White, 350, 650, 10, " vamos, filho");
		break;
	case 102:
		write(1, window, 0.03, Color::White, 350, 650, 10, " vamos, filho\n sua mãe está nos esperando em casa\n estavamos ansiosos por sua alta");
		break;
	case 103:
		write(1, window, 0.03, Color::White, 350, 650, 10, " estavamos ansiosos por sua alta\n não precisa ter medo, estou aqui");
		break;
	case 104:
		write(1, window, 0.03, Color::White, 350, 650, 10, " estavamos ansiosos por sua alta\n não precisa ter medo, estou aqui");
		break;
	case 100:
		write(1, window, 0.03, Color::White, 350, 650, 10, "alguém pode iluminar?");
		break;

	default:
		write(1, window, 0.03, Color::White, 50, 650, 10, "");
		break;

	}
}

void draw_menu(int* current_scr,Texture * textures ,RenderWindow *window) {
	// Create text
	IntRect rec(0,0,800,600);
	Sprite menu(textures[0],rec);
	menu.setScale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);
	menu.setPosition(0, 0);

	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	Text logo;
	Text opt1;
	Text opt2;
	Text opt3;
	logo.setFont(font);
	opt1.setFont(font);
	opt2.setFont(font);
	opt3.setFont(font);
	logo.setString("Lunare");
	opt1.setString("Iniciar");
	opt2.setString("Creditos");
	opt3.setString("Sair");
	logo.setCharacterSize((*window).getSize().y * 0.08);
	opt1.setCharacterSize((*window).getSize().y * 0.05);
	opt2.setCharacterSize((*window).getSize().y * 0.05);
	opt3.setCharacterSize((*window).getSize().y * 0.05);
	logo.setPosition((*window).getSize().x / 2 - ((*window).getSize().y * 0.08 * 21) / 2 / 2, (*window).getSize().y / 2 / 2 - (*window).getSize().y * 0.08 / 2);
	opt1.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 3);
	opt2.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 4);
	opt3.setPosition((*window).getSize().x * 0.02, (*window).getSize().y * 0.5 + (*window).getSize().y * 0.08 * 5);

	// Menu events
	if (opt1.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt1.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 1;
	}
	else if (opt2.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt2.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 2;
	}
	else if (opt3.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		opt3.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			(*window).close();
	}

	// Draw
	(*window).draw(menu);
	(*window).draw(logo);
	(*window).draw(opt1);
	(*window).draw(opt2);
	(*window).draw(opt3);
}

Sprite get_prop(Clock clock, Texture* textures, int line, float x, float y) {
	IntRect propRect(0,0,50,50);
	Sprite prop(textures[5], propRect);
	animate(clock, &propRect, &prop, 50, 50, 3, line, 3);
	prop.setPosition(x, y);
	return prop;
}

void draw_gameover(Clock clock,int* current_scr, Texture* textures, RenderWindow* window,int*room,shadow* main, int propLine[]) {

	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	IntRect die(0, 0, 800, 600);
	Sprite died(textures[13], die);
	died.setPosition(0, 0);
	died.setScale((*window).getSize().x/800.0, (*window).getSize().y / 600.0);
	animate(clock, &die, &died, 800, 600, 4, 0, 10);
	(*window).draw(died);

	Text gameover;
	gameover.setFont(font);
	gameover.setString("Você perdeu!");
	gameover.setCharacterSize((*window).getSize().y * 0.08);
	gameover.setPosition((*window).getSize().x / 2 - gameover.getGlobalBounds().width / 2, (*window).getSize().y / 2 / 2 - (*window).getSize().y * 0.08 / 2);
	Text menu;
	menu.setFont(font);
	menu.setString("Voltar ao menu");
	menu.setCharacterSize((*window).getSize().y * 0.05);
	menu.setPosition((*window).getSize().x / 2 + 50, (*window).getSize().y / 2 / 2 * 3);
	Text retry;
	retry.setFont(font);
	retry.setString("Tentar novamente");
	retry.setCharacterSize((*window).getSize().y * 0.05);
	retry.setPosition((*window).getSize().x / 2 - 50 - retry.getGlobalBounds().width, (*window).getSize().y / 2 / 2 * 3);

	// Menu events
	if (menu.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		menu.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}
	else if (retry.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		retry.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left)) {
			*current_scr = 1;
			init_main(main);
			*room = 0;
		}
	}

	(*window).draw(gameover);
	(*window).draw(menu);
	(*window).draw(retry);
}

void draw_game(Sound *sound,Texture* textures, double delta, Clock clock, shadow* main, int* room, int* current_scr, RenderWindow* window, Event& event, int *cursorLine, int *propLine) {
	int h;
	/*textures[0] = menu;
	textures[1] = floor;
	textures[2] = sky;
	textures[3] = tree1;
	textures[4] = tree2;
	textures[5] = well;
	textures[6] = uparrow;
	textures[7] = textbox;
	textures[8] = sun;
	textures[9] = LUNA_TEXT;
	textures[10] = charluna;
	textures[11] = gansoed;
	textures[12] = vitrine;
	textures[13] = transition;
	textures[14] = room;
	textures[15] = shop;
	textures[16] = seller;
	textures[17] = lucisky;
	textures[18] = house;
	textures[19] = goosebullet;
	textures[20] = gansofly;
	textures[21] = ganso;
	textures[22] = forest;
	textures[23] = cloud;
	textures[24] = bread;
	textures[25] = ball;
	textures[26] = boom;*/
		
	IntRect rectMc(0, 0, 160, 160);
	Sprite mc(textures[0], rectMc);
	Texture rooml;


	
	int tx;

	if(*room!=1)
		tx=main->tx;
	else
		tx=1080;

	
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		*current_scr = 0;
	}
	if (main->cs == 1) {
		
		if ((main->cs ) == 0 && main->a[0] == 0)
			main->a[0] = 1;
		for (int i = 0; i < 10; i++)
			propLine[i] = 0;
		main->dir = 1;
		main->line = 0;
		main->chat = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && main->wx>8*5 &&(*room!=6||(main->endline!=0||( main->endline<500) ))) {

	
		main->line = 1;
		main->dir = -1;
		main->x = main->x - 8 / delta;

	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && main->x < main->tx-15*5 &&(*room != 6 || (main->endline != 0))) {
		main->line = 1;
		main->dir = 1;
		main->x = main->x + 8 / delta;

	}
	else {
		main->line = 0;
	}

	//flip
	if (main->dir == -1) {
		mc.scale(-1, 1);


	}
	//move all
	
	if (main->x < 400)
		main->wx = main->x;
	else if (main->x > (main->tx - 400))
		main->wx =800-(main->tx-main->x);
	else
		main->wx = 400;
	//set parameters

	animate(clock, &rectMc, &mc, 5 * 32, 5 * 32, main->frames, main->line, 10);
	IntRect rerom(0, 0, tx, 600);
	Sprite rom(textures[1], rerom);
	rom.setScale((*window).getSize().x / (800.0), (*window).getSize().y / 600.0);
	animate(clock, &rerom, &rom, tx, 600, 2, 0, 4);

	rom.setPosition((main->wx-main->x)* (*window).getSize().x / 800.0, 0);
	
	mc.setPosition((main->wx - (((main->dir + 1) / 2 -1)* 32*5) - 32 * 2) * ((*window).getSize().x) / 800.0, main->y * ((*window).getSize().y) / 600.0);
	mc.scale((*window).getSize().x / 800.0, (*window).getSize().y / 600.0);

	// Draw

	switch (*room)
	{
	case 0:
		break;
	}

}

void draw_credits_gamso(RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	Text credits;
	credits.setFont(font);
	credits.setString("Uma produção Lunare Team e");
	credits.setCharacterSize((*window).getSize().y*0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y*0.02);

	// Create texture
	Texture texture;
	if (!texture.loadFromFile("img/gamso.png")){
		cout << "Error loading texture" << endl;
	}
	texture.setSmooth(false);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale((*window).getSize().y / sprite.getLocalBounds().width, (*window).getSize().y / sprite.getLocalBounds().height);
	sprite.setPosition((*window).getSize().x/2-sprite.getGlobalBounds().width/2-22, 0);
	
	(*window).draw(credits);
	(*window).draw(sprite);
}

void draw_credits(int* current_scr, RenderWindow *window) {
	// Create text
	Font font;
	if (!font.loadFromFile("fonts/pc98.ttf")) {
		cout << "Error loading fonts" << endl;
		scanf("%*c");
	}
	Text voltar;
	voltar.setFont(font);
	voltar.setString("Voltar");
	voltar.setCharacterSize((*window).getSize().y * 0.05);
	voltar.setPosition((*window).getSize().x*0.02, (*window).getSize().y*0.5 + (*window).getSize().y * 0.08 * 5);
	Text credits;
	credits.setFont(font);
	credits.setString("Programador de engine: João Bueno (@rito_jobu)\nDireção: João Bueno (@rito_jobu)\nProgramador de gameplay: Matheus Ramos\nArte e Som: Matheus Ramos\n\nCom a colaboração do grupo GAMSo");
	credits.setCharacterSize((*window).getSize().y * 0.05);
	credits.setPosition((*window).getSize().x/2-credits.getGlobalBounds().width/2, (*window).getSize().y/2-credits.getGlobalBounds().height/2);

	// Mouse events
	if (voltar.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)) {
		voltar.setFillColor(Color::Magenta);
		if (Mouse::isButtonPressed(Mouse::Left))
			* current_scr = 0;
	}

	// Draw
	(*window).draw(voltar);
	(*window).draw(credits);
}

void draw_scr(Texture* textures,double delta,Clock clock,shadow* main,int* room,int* current_scr, RenderWindow *window, Event &event,Sound *sound, int *cursorLine, int *propLine) {
	/*
	 *  0 - Menu
	 *  1 - Game
	 *  2 - Credits
		3-  F
	 */

	switch (*current_scr) {
	case 0:
		draw_menu(current_scr,textures, window);
		init_main(main);
		*room = 0;
		for (int i = 0; i < 10; i++)
			propLine[i] = 0;

		break;
	case 1:
		draw_game(sound,textures,delta, clock,main,room,current_scr, window, event, cursorLine, propLine);
		break;
	case 2:
		draw_credits(current_scr, window);
		break;
	case 3:
		draw_gameover(clock,current_scr, textures,window,room,main,propLine);
		break;
	default:
		break;
	}
}

Texture* load_textures() {
	Texture *textures;
	textures=(Texture*)malloc(sizeof(Texture) * 27);

	Texture menu;//
	if (!menu.loadFromFile("img/menu.png", sf::IntRect(0, 0, 800, 600))) {
		perror("failed to load menu image");
		scanf("%*c");
	}
	
	Texture gansoed;//
	if (!gansoed.loadFromFile("img/animatedganso.png", sf::IntRect(0, 0, 736, 256))) {
	perror("failed to load cutscene goose image");
		scanf("%*c");
	}
	Texture ball;//
	if (!ball.loadFromFile("img/ball.png", sf::IntRect(0, 0, 128, 32))) {
		perror("failed to load cutscene goose image");
		scanf("%*c");
	}
	Texture boom;//
	if (!boom.loadFromFile("img/boom.png", sf::IntRect(0, 0, 600, 880))) {
		perror("failed to load fire image");
		scanf("%*c");
	}
	Texture bread;//
	if (!bread.loadFromFile("img/bread.png", sf::IntRect(0, 0, 32,20))) {
		perror("failed to load bread image");
		scanf("%*c");
	}
	Texture charluna;//
	if (!charluna.loadFromFile("img/charluna.png", sf::IntRect(0, 0, 276, 640))) {
		perror("failed to load charluna image");
		scanf("%*c");
	}
	Texture cloud;//
	if (!cloud.loadFromFile("img/cloud.png", sf::IntRect(0, 0, 2048, 512))) {
		perror("failed to load cload image");
		scanf("%*c");
	}
	Texture floor;//
	if (!floor.loadFromFile("img/floor.png", sf::IntRect(0, 0, 480, 480))) {
		perror("failed to load floor image");
		scanf("%*c");
	}
	Texture forest;//
	if (!forest.loadFromFile("img/forest.png", sf::IntRect(0, 0, 480, 480))) {
		perror("failed to load forest image");
		scanf("%*c");
	}
	Texture ganso;
	if (!ganso.loadFromFile("img/ganso.png", sf::IntRect(0, 0, 138, 512))) {
		perror("failed to load ganso image");
		scanf("%*c");
	}
	Texture gansofly;//
	if (!gansofly.loadFromFile("img/gansofly.png", sf::IntRect(0, 0, 350, 140))) {
		perror("failed to load gansosly image");
		scanf("%*c");
	}
	Texture goosebullet;//
	if (!goosebullet.loadFromFile("img/goosebullet.png", sf::IntRect(0, 0, 32, 20))) {
		perror("failed to load feather image");
		scanf("%*c");
	}	
	Texture house;//
	if (!house.loadFromFile("img/house.png", sf::IntRect(0, 0, 384, 384))) {
		perror("failed to load house image");
		scanf("%*c");
	}
	Texture lucisky;//
	if (!lucisky.loadFromFile("img/lucisky.png", sf::IntRect(0, 0, 800, 800))) {
		perror("failed to load lucisky image");
		scanf("%*c");
	}
	Texture LUNA_TEXT;//
	if (!LUNA_TEXT.loadFromFile("img/LUNA_TEXT.png", sf::IntRect(0, 0, 2304, 3456))) {
		perror("failed to load lucisky image");
		scanf("%*c");
	}
	Texture room;//
	if (!room.loadFromFile("img/room.png", sf::IntRect(0, 0, 800, 600))) {
		perror("failed to load room image");
		scanf("%*c");
	}
	Texture seller;//
	if (!seller.loadFromFile("img/seller.png", sf::IntRect(0, 0, 252, 252))) {
		perror("failed to load seller image");
		scanf("%*c");
	}
	Texture shop;//
	if (!shop.loadFromFile("img/shop.png", sf::IntRect(0, 0, 800, 600))) {
		perror("failed to load shop image");
		scanf("%*c");
	}
	Texture sky;//
	if (!sky.loadFromFile("img/sky.png", sf::IntRect(0, 0, 800, 800))) {
		perror("failed to load sky image");
		scanf("%*c");
	}
	Texture sun;//
	if (!sun.loadFromFile("img/sun.png", sf::IntRect(0, 0, 1152, 92))) {
		perror("failed to load sun image");
		scanf("%*c");
	}
	Texture textbox;//
	if (!textbox.loadFromFile("img/textbox.jpg", sf::IntRect(0, 0, 710, 135))) {
		perror("failed to load textbox image");
		scanf("%*c");
	}
	Texture transition;//
	if (!textbox.loadFromFile("img/transition.png", sf::IntRect(0, 0, 7200, 600))) {
		perror("failed to load transition image");
		scanf("%*c");
	}
	Texture tree1;//
	if (!tree1.loadFromFile("img/tree1.png", sf::IntRect(0, 0, 320, 320))) {
		perror("failed to load tree1 image");
		scanf("%*c");
	}
	Texture tree2;//
	if (!tree2.loadFromFile("img/tree2.png", sf::IntRect(0, 0, 320, 320))) {
		perror("failed to load tree2 image");
		scanf("%*c");
	}
	Texture uparrow;//
	if (!uparrow.loadFromFile("img/uparrow.png", sf::IntRect(0, 0, 96, 32))) {
		perror("failed to load uparrow image");
		scanf("%*c");
	}
	Texture vitrine;//
	if (!vitrine.loadFromFile("img/vitrine.png", sf::IntRect(0, 0, 64, 32))) {
		perror("failed to load vitrine image");
		scanf("%*c");
	}
	Texture well;//
	if (!well.loadFromFile("img/well.png", sf::IntRect(0, 0, 480, 512))) {
		perror("failed to load well image");
		scanf("%*c");
	}
	textures[0] = menu;
	textures[1] = floor;
	textures[2] = sky;
	textures[3] = tree1;
	textures[4] = tree2;
	textures[5] = well;
	textures[6] = uparrow;
	textures[7] = textbox;
	textures[8] = sun;
	textures[9] = LUNA_TEXT;
	textures[10] = charluna;
	textures[11] = gansoed;
	textures[12] = vitrine;
	textures[13] = transition;
	textures[14] = room;
	textures[15] = shop;
	textures[16] = seller;
	textures[17] = lucisky;
	textures[18] = house;
	textures[19] = goosebullet;
	textures[20] = gansofly;
	textures[21] = ganso;
	textures[22] = forest;
	textures[23] = cloud;
	textures[24] = bread;
	textures[25] = ball;
	textures[26] = boom;

	return textures;

}

int main(void) {
	int current_scr[1] = { 0 }, room = 0, propLine[10] = {0,0,0,0,0,0,0,0,0,0};

	// Initialize clock
	Clock clock;
	// Initialize window
	RenderWindow window(VideoMode::getDesktopMode(), "Lunare", Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	shadow main;
	init_main(&main);
	Texture* textures;
	if (clock.getElapsedTime().asSeconds() <= 10)
		draw_credits_gamso(&window);
	textures = load_textures();
	Sprite cursor(textures[8]);
	IntRect cursorRect(0,0,96,96);
	SoundBuffer walk,bgm;
	if (!walk.loadFromFile("sound/walk.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
	}
	if (!bgm.loadFromFile("sound/bgm.wav")) {
		cout << "Error loading sound" << endl;
		scanf("%*c");
	}
	Sound sound,bg;
	sound.setBuffer(walk);
	bg.setBuffer(bgm);

	double nt,ot=0,delta;
	while( window.isOpen()) {		

		Time time;
		time = clock.getElapsedTime();
		nt = time.asMicroseconds();
	
		delta = 50000/(nt - ot) ;
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)
				window.close();
		}
		

		window.clear();
		int cursorLine = 1;
		if (time.asSeconds() > 10)
		 {
			draw_scr(textures, delta, clock, &main, &room, current_scr, &window, event, &sound, &cursorLine, propLine);
			if (bg.getStatus() != bg.Playing && *current_scr == 1)
				bg.play();
			else if (bg.getStatus() == bg.Playing && *current_scr == 0)
				bg.stop();
		}
		cursorRect.top = 96 * cursorLine;
		cursor.setTextureRect(cursorRect);
		cursor.setOrigin(48, 48);
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
		animate(clock, &cursorRect, &cursor, 96,96, 12,0, 4);
		window.draw(cursor);
		window.display();
		ot = nt;
	}
	free(textures);
	return 0;

}