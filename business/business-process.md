# Business Process

From raw resources to the customer's door.

```
Supplier -> Stock -> Order (website) -> Print -> Post-process -> Electronics/RGB -> QC -> Packaging -> Shipping -> Delivery -> Support
```

## 1. Sourcing (resources)
| Resource | Supplier | Price | Lead time | Notes |
|---|---|---|---|---|
| Filament (PLA / PETG) | | | | |
| LEDs (addressable strips) | | | | |
| Microcontrollers (Arduino / ESP32) | | | | |
| Power supplies | | | | |
| Magnets / hardware / screws | | | | |
| Packaging (boxes, foam, tape) | | | | |

Reorder thresholds and minimum stock: _TBD_.

## 2. Order flow
1. Customer designs the panel on the website configurator.
2. Order is validated (component compatibility, size).
3. Bill of materials and print job list are generated.
4. Payment confirmed, confirmation email sent.

## 3. Production
- Print in batches by material/colour.
- Post-processing: support removal, sanding, fit test.
- Electronics: LED strip install, controller flash and test.
- Quality check: fit, lighting, stability.

## 4. Packaging
- Box sizes: _TBD_
- Protective material, instruction card, small parts bag.
- Record **packaged weight and dimensions** per order (see the product catalog).

## 5. Shipping & delivery
| Item | Details |
|---|---|
| Carrier(s) | _TBD_ (compare national post office vs. couriers) |
| Service levels | Standard / Expedited |
| Order weight | Sum of packaged weights |
| Dimensional weight | L x W x H / carrier divisor |
| Shipping cost | Pass-through vs. flat rate vs. free above a threshold |
| Delivery time | |
| Tracking | Tracking number emailed to customer |
| International | TBD (customs, duties, electronics/battery restrictions) |

Fill in with real carrier quotes:
| Package | Weight | Dimensions | Destination | Price |
|---|---|---|---|---|
| Small (accessories) | | | | |
| Medium (panel + mounts) | | | | |
| Large (big panel) | | | | |

## 6. After-sales
- Returns and warranty policy: _TBD_
- Replacement parts printed on demand
- Support channel: email / Discord / social

## 7. Roles
| Task | Owner |
|---|---|
| Design / CAD | |
| Printing / production | |
| Website | |
| Shipping / support | |
| Finance / admin | |
