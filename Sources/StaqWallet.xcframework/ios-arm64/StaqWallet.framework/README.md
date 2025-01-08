# Wallet Pay


### WalletPayParams

The `WalletPayParams` struct provides the following parameters:
- `totalAmount`: The total transaction amount.
- `subtotalAmount`: The subtotal amount before fees.
- `currencyCode`: The currency code (default is "SAR").
- `fees`: The fees associated with the transaction.
- `productId`: The unique identifier for the product.
- `sku`: The stock-keeping unit for the product.
- `narative`: An optional narrative or description for the transaction.

Initialization example:

```swift
let params = WalletPayParams(
    totalAmount: 150.0,
    subtotalAmount: 140.0,
    currencyCode: "SAR",
    fees: 10.0,
    productId: "12345",
    sku: "ABC-678",
    narative: "Payment for Order #12345"
)
```

---

### SwiftUI

#### WalletPayView

Here is an example of how to use `WalletPayView` in a SwiftUI app:

```swift
import SwiftUI

struct ContentView: View {
    @State var isSelected = false

    var body: some View {
        WalletPayView(
            isSelected: $isSelected,
            variant: .inline,
            balance: 1000.0,
            params: WalletPayParams(/* your parameters */)
        )
        .onTapGesture {
            isSelected.toggle()
        }
    }
}
```

#### Parameters

- `isSelected`: A `Binding<Bool>` property to toggle selection state.
- `variant`: A `WalletPayView.Variant` enum value to specify the view style (`inline` or `breakdown`).
- `balance`: A `Double` representing the wallet balance.
- `params`: A `WalletPayParams` object to provide additional configuration.

---

#### WalletPayDetailsView

The `WalletPayDetailsView` is a SwiftUI component designed for displaying detailed wallet payment transactions.

Here is an example of how to use `WalletPayDetailsView`:

```swift
WalletPayDetailsView(
    balance: 1000.0,
    params: WalletPayParams(/* your parameters */)
)
```

#### Parameters

- `balance`: A `Double` representing the wallet balance.
- `params`: A `WalletPayParams` object containing transaction details.

---

### UIKit

For UIKit integration, use the `UIWalletPayView` class, which wraps the SwiftUI view in a `UIView`.

Here is how to integrate `UIWalletPayView` into a UIKit application:

```swift
import UIKit
import SwiftUI

class ViewController: UIViewController {
    var walletPayView: UIWalletPayView!

    override func viewDidLoad() {
        super.viewDidLoad()

        walletPayView = UIWalletPayView(
            frame: CGRect(x: 0, y: 0, width: 300, height: 100),
            isSelected: false,
            variant: .inline,
            balance: 1000.0,
            params: WalletPayParams(/* your parameters */)
        )

        let tapGesture = UITapGestureRecognizer(
            target: self,
            action: #selector(handleTap)
        )
        walletPayView.addGestureRecognizer(tapGesture)

        view.addSubview(walletPayView)
        walletPayView.center = view.center
    }

    @objc private func handleTap() {
        walletPayView.setSelected(!walletPayView.isSelected)
    }
}
```

#### Initialization

`UIWalletPayView` can be initialized with:

- `frame`: The frame for the view.
- `isSelected`: A `Bool` to set the initial selection state.
- `variant`: A `WalletPayView.Variant` enum value to specify the view style (`inline` or `breakdown`).
- `balance`: A `Double` representing the wallet balance.
- `params`: A `WalletPayParams` object to provide additional configuration.

#### Methods
- `setSelected(_ isSelected: Bool)`: Updates the selection state programmatically.

---

### Additional Information

#### Animations
The selection state is animated using a spring animation:
```swift
.animation(.spring, value: isSelected)
```
