import Postcode from "@actbase/react-daum-postcode";

interface AddressSearchProps {
    // callback for setting state
}

const AddressSearch = (prop: AddressSearchProps) => {

    const handleAddressSelect = (data: any) => {
        console.log(data);
        // set state
    };

    const handleError = (error: any) => {
        // error handling
    };

    return (
        <Postcode
            style={{width: '100%', height: '100%'}}
            jsOptions={{animation: true, hideMapBtn: true}}
            onSelected={handleAddressSelect}
            onError={handleError}
        />
    );
}

export default AddressSearch;