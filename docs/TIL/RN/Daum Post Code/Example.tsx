import React, {useState} from 'react';
import {Text, View, TouchableOpacity, Button, Modal} from 'react-native';
import AddressSearch from "@/components/AddressSearch";

const Example = () => {
    const [address, setAddress] = useState('');
    const [isModalVisible, setModalVisible] = useState(false);

    const toggleAddressSearchModal = () => {
        setModalVisible(true);
    };

    const handleUserAddressSearch = (address: string) => {
        setAddress(address);
        setModalVisible(false);
    };

    return (
        <View>
            <View>
                <Text>{address}</Text>
                <TouchableOpacity onPress={toggleAddressSearchModal}>
                    <Text>주소 검색 버튼</Text>
                </TouchableOpacity>
            </View>
            <Modal visible={isModalVisible} animationType={'slide'}>
                <View>
                    <AddressSearch onAddressSelect={handleUserAddressSearch}/>
                    <Button title="닫기" onPress={() => setModalVisible(false)}/>
                </View>
            </Modal>
        </View>
    );
};