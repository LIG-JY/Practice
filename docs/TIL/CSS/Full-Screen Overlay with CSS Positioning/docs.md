# Full-Screen Overlay with CSS Positioning

```css
.PopupOverlay {
    position: fixed;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: rgba(0, 0, 0, 0.5);
    display: flex;
    align-items: center;
    justify-content: center;
}
```

- `position: fixed`:
    - PopupOverlay 가 viewport 기준으로 고정 됨
    - 페이지가 스크롤 되더라도 유지됨
    - 상위 컨테이너뿐만 아니라 표시되는 화면 전체에 걸치게 됨
- `top: 0, left: 0, right: 0, bottom: 0`:
    - PopupOverlay 가 viewport 전체를 덮도록
    - 절대 위치 지정 요소에서 top, left, right, bottom 은 모서리로 부터 거리
      - `position: fixed` 는 절대 위치 지정 요소에 포함됨

- [reference](https://developer.mozilla.org/ko/docs/Web/CSS/position)
