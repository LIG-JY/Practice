# Value

> The value to show for the text input. TextInput is a controlled component, which means the native value will be forced
> to match this value prop if provided. For most uses, this works great, but in some cases this may cause flickering -
> one
> common cause is preventing edits by keeping value the same. In addition to setting the same value, either set
> editable={false}, or set/update maxLength to prevent unwanted edits without flicker.

## Controlled Component

- React에서 상태를 통해 그 값을 완전히 관리하는 컴포넌트
- 사용자의 입력과 같은 상호작용을 통해 그 값이 업데이트 되고, 다시 컴포넌트의 표시 값으로 반영됨

## Native Value

- 모바일 플랫폼에서 직접 관리하는 입력 필드의 실제 값
- React Native의 TextInput 컴포넌트는 value prop을 통해 입력 필드의 값을 제어함
    - 결과적으로 TextInput 컴포넌트의 입력 필드의 값 == 네이티브 입력 필드의 값
    - 브리지 메커니즘
        - React Native에서 JavaScript 코드와 네이티브 플랫폼의 UI 컴포넌트 간의 통신

## Flickering

- UI가 갑자기 깜빡거리고 불안정하게 보이는 현상
- 원인
    - 무한 렌더링
    - 불필요한 업데이트
    - Controlled Component
        - 입력 필드의 value가 고정되어 있어 사용자가 입력할 수 없거나, 입력을 막으면서 UI가 깜박이는 경우
        - 만약 TextInput의 Value가 동일한 값으로 설정되면, 사용자가 입력을 시도할 때 TextInput이 값을 유지하려고 시도하면서 깜박일 수 있음

```typescript jsx
import React, {useState} from 'react';
import {View, TextInput, StyleSheet} from 'react-native';

const FixedValueTextInput = () => {
    const [text, setText] = useState('Fixed Value');

    const handleChangeText = (inputText: string) => {
        setText('Fixed Value');
    };

    return (
        <View style={styles.container}>
            <TextInput
                style={styles.input}
                value={text}
                onChangeText={handleChangeText}
            />
        </View>
    );
};

export default FixedValueTextInput;
```
