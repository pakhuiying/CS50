import UIKit

class ViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    @IBOutlet var imageView: UIImageView!

    let context = CIContext()
    var original: UIImage!

    @IBAction func applySepia() {
        if original == nil {
            return
        }

        let filter = CIFilter(name: "CISepiaTone")
        filter?.setValue(CIImage(image: original), forKey: kCIInputImageKey)
        filter?.setValue(1.0, forKey: kCIInputIntensityKey)
        display(filter: filter!)
    }

    @IBAction func applyNoir() {
        if original == nil {
            return
        }

        let filter = CIFilter(name: "CIPhotoEffectNoir")
        filter?.setValue(CIImage(image: original), forKey: kCIInputImageKey)
        display(filter: filter!)
    }

    @IBAction func applyVintage() {
        if original == nil {
            return
        }

        let filter = CIFilter(name: "CIPhotoEffectProcess")
        filter?.setValue(CIImage(image: original), forKey: kCIInputImageKey)
        display(filter: filter!)
    }
    
    @IBAction func applyBloom() {
        if original == nil {
            return
        }

        let filter = CIFilter(name: "CIBloom")
        filter?.setValue(CIImage(image: original), forKey: kCIInputImageKey)
        filter?.setValue(0.5, forKey: kCIInputIntensityKey)
        filter?.setValue(10, forKey: kCIInputRadiusKey)
        display(filter: filter!)
    }
    
    @IBAction func applyComic() {
        if original == nil {
            return
        }

        let filter = CIFilter(name: "CIComicEffect")
        filter?.setValue(CIImage(image: original), forKey: kCIInputImageKey)
        display(filter: filter!)
    }

    @IBAction func choosePhoto(_ sender: UIBarButtonItem) {
        if UIImagePickerController.isSourceTypeAvailable(.photoLibrary) {
            let picker = UIImagePickerController()
            picker.delegate = self
            picker.sourceType = .photoLibrary
            self.navigationController?.present(picker, animated: true, completion: nil)
        }
    }

    func display(filter: CIFilter) {
        let output = filter.outputImage!
        imageView.image = UIImage(cgImage: self.context.createCGImage(output, from: output.extent)!)
    }
    
    @objc func savedImage(_ im:UIImage, error:Error?, context:UnsafeMutableRawPointer?) {
        if let err = error {
            print(err)
            return
        } //A typical error would be if the user refused permission in the system dialog. If all goes well, the error will be nil and you'll know that the write succeeded.
        print("success")
    }
    
    @IBAction func savePhoto(){
        //if imageView.image != nil {
        let output = imageView.image!
        /*The idea of the second two parameters, self and #selector(savedImage), is that your savedImage method in self will be called back after the image is saved (or not saved).*/
        
        UIImageWriteToSavedPhotosAlbum(output, self, #selector(savedImage), nil)
        //}
    }

    func imagePickerController(
        _ picker: UIImagePickerController,
        didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]
    ) {
        self.navigationController?.dismiss(animated: true, completion: nil)
        if let image = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            imageView.image = image
            original = image
        }
    }
}
