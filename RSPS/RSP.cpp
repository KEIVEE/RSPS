#include "RSP.h"
#include <random>

Sprite RSP::getSprite() {
    return sprite;
}

void RSP::move(Vector2f& v, RenderWindow& window) {
    //객체가 움직이는 메커니즘
    if (sprite.getPosition().x <= window.getSize().x - sprite.getGlobalBounds().width && 
        sprite.getPosition().y <= window.getSize().y - sprite.getGlobalBounds().height &&
        sprite.getPosition().x >= 0 && sprite.getPosition().y >= 0) {
        //객체가 윈도우 창을 벗어나지 않는 하에
            sprite.move(v);
            //v방향으로 움직이지만
    }

    //맨 끝에서 1픽셀에 닿는다면: 여기서 중요한 것은 else를 쓰지 않는다는 것. else를 써버리면 요 아래 if들은 절대로 실행되지 않는다.
    if ((sprite.getPosition().x >= window.getSize().x - sprite.getGlobalBounds().width-1 || sprite.getPosition().x <= 1) &&
        (sprite.getPosition().y <= window.getSize().y - sprite.getGlobalBounds().height-1 && sprite.getPosition().y >= 1)) {
        //왼쪽 혹은 오른쪽 모서리에 닿는다면: 그러면서 y는 정상적인 위치에 있다면
        //정상적인 위치라 함은 윈도우 안에 보일 범위 말하는 것: 더 세부적으로 말하면 y좌표 1부터 879까지.
        sprite.move(-v.x, v.y);
        //반대쪽으로 튕겨내 주기.
    }

    if ((sprite.getPosition().y >= window.getSize().y - sprite.getGlobalBounds().height-1 || sprite.getPosition().y <= 1) &&
        (sprite.getPosition().x <= window.getSize().x - sprite.getGlobalBounds().width-1 && sprite.getPosition().x >= 1)) {
        //위 혹은 아래 모서리에 닿는다면: 그러면서 x는 정상적인 위치에 있다면
        sprite.move(v.x, -v.y);
        //반대쪽으로 튕겨내 주기.
    }

    if ((sprite.getPosition().y >= window.getSize().y - sprite.getGlobalBounds().height - 1 || sprite.getPosition().y <= 1) &&
        (sprite.getPosition().x >= window.getSize().x - sprite.getGlobalBounds().width - 1 || sprite.getPosition().x <= 1)) {
        //만약 구석으로 갔다:
        sprite.move(-v.x, -v.y);
        //끝에 닿을 수 없도록 튕겨내 주기.
    }
    /*
    맨 처음 if는 윈도우 범위 안에서 움직이게 하는데, 이것만 둔다면 모서리에 닿았을 때 다시 안쪽으로 들어오지 못하는 현상이 발생
    그래서 맨 끝에 1프레임을 내주고 실제로 움직이는 것은 그 1프레임을 제외하고 그 안쪽에서만 움직이도록 하면
    모서리에 닿았던(실은 닿지는 않지만 닿은 것처럼 보이는) 객체도 잘 돌아와서 쫓고 피하고 할 수 있다.
    */

}

void RSP::draw(RenderWindow& window) {
    window.draw(sprite);
} 


bool RSP::hitby(RSP& other) { //실행될 일이 없지만 발표할 때 잘 써먹을 수 있을 듯한 버추얼 함수.
    return false;
}


void RSP::setPosition(Vector2f& position) {
    sprite.setPosition(position);
}